#include <components/Collision2DComponent.h>
#include <components/InputComponent.h>
#include <components/TextureComponent.h>
#include <entities/PlayerGameEntity.h>
#include <entities/ProjectileEntity.h>
#include <utility/Geometry.h>

#include <algorithm>

PlayerGameEntity::PlayerGameEntity() = default;

void PlayerGameEntity::AddRequired(SDL_FRect transform, SDL_Renderer* renderer, uint32_t screenWidth) {
    GameEntity::AddRequired(transform);

    m_XMax = static_cast<double>(screenWidth) - GetTransform()->m_Rectangle.width();

    std::shared_ptr<TextureComponent> characterTexture = std::make_shared<TextureComponent>();
    characterTexture->CreateTextureComponent(renderer, "../assets/hero.bmp");
    AddComponent(characterTexture);

    std::shared_ptr<Collision2DComponent> col = std::make_shared<Collision2DComponent>();
    AddComponent(col);

    std::shared_ptr<ProjectileEntity> projectile = std::make_shared<ProjectileEntity>();
    projectile->AddRequired(transform, renderer);
    AddChild(projectile);

    std::shared_ptr<InputComponent> inputController = std::make_shared<InputComponent>();
    std::function<void(float, const std::vector<uint8_t> keys)> inputHandler =
        [inputController, projectile, this](float deltaTime, const std::vector<uint8_t> keys) {
            // For now -- keep a reference to our first sprite
            auto ge = inputController->GetGameEntity();
            auto& transform =
                ge->GetComponent<TransformComponent>(ComponentType::TransformComponent).value()->m_Rectangle;

            if (keys[SDL_SCANCODE_LEFT]) {
                Geometry::SetX(transform, std::max(m_XMin, Geometry::GetX(transform) - m_Speed * deltaTime));
            } else if (keys[SDL_SCANCODE_RIGHT]) {
                Geometry::SetX(transform, std::min(m_XMax, Geometry::GetX(transform) + m_Speed * deltaTime));
            }

            if (keys[SDL_SCANCODE_UP]) {
                SDL_Log("Launching!");
                // Don't like dynamic casts, but we'll do this for now until we either implement CRTP for entities or go
                // another route; don't want to jump ahead in the course and have to redo a ton of work
                projectile->Launch(static_cast<float>(Geometry::GetX(transform)),
                                   static_cast<float>(Geometry::GetY(transform)), -200);
            }
        };
    inputController->SetOnKeypress(inputHandler);
    AddComponent(inputController);
}

[[nodiscard]] std::shared_ptr<ProjectileEntity> PlayerGameEntity::GetProjectile() const {
    // Don't like dynamic casts, but we'll do this for now until we either implement CRTP for entities or go another
    // route; don't want to jump ahead in the course and have to redo a ton of work
    return dynamic_pointer_cast<ProjectileEntity>(m_Children[0]);
}