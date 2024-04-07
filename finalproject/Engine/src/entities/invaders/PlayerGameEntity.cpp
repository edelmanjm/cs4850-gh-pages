#include <ResourceManager.h>
#include <components/Collision2DComponent.h>
#include <components/InputComponent.h>
#include <components/TextureComponent.h>
#include <entities/ProjectileEntity.h>
#include <entities/invaders/PlayerGameEntity.h>
#include <utility/Geometry.h>

#include <algorithm>

PlayerGameEntity::PlayerGameEntity() = default;

void PlayerGameEntity::AddRequired(SDL_FRect transform, SDL_Renderer* renderer, uint32_t screenWidth) {
    GameEntity::AddRequired();

    m_XMin = -transform.x;
    m_XMax = static_cast<double>(screenWidth) - transform.w - transform.x;

    std::shared_ptr<TextureComponent> characterTexture =
        std::make_shared<TextureComponent>(ResourceManager::Instance().LoadTexture(renderer, "../assets/hero.bmp"),
                                           Geometry::AsH2D(transform));
    AddComponent(characterTexture);

    std::shared_ptr<Collision2DComponent> col = std::make_shared<Collision2DComponent>(Geometry::AsH2D(transform));
    AddComponent(col);

    std::shared_ptr<ProjectileEntity> projectile = std::make_shared<ProjectileEntity>();
    projectile->AddRequired(Geometry::AsH2D(transform), renderer);
    AddChild(projectile);

    std::shared_ptr<InputComponent> inputController = std::make_shared<InputComponent>();
    std::function<void(float, const std::vector<uint8_t> keys)> inputHandler =
        [inputController, projectile, this](float deltaTime, const std::vector<uint8_t> keys) {
            // For now -- keep a reference to our first sprite
            auto ge = inputController->GetGameEntity();
            auto& transform =
                ge->GetComponent<TransformComponent>(ComponentType::TransformComponent).value()->m_Transform;

            h2d::Point2d origin(0, 0);
            h2d::Point2d transformed = GetTransform()->m_Transform * origin;

            if (keys[SDL_SCANCODE_LEFT]) {
                transform.setTranslation(std::max(m_XMin, transformed.getX() - m_Speed * deltaTime),
                                         transformed.getY());
            } else if (keys[SDL_SCANCODE_RIGHT]) {
                transform.setTranslation(std::min(m_XMax, transformed.getX() + m_Speed * deltaTime),
                                         transformed.getY());
            }

            if (keys[SDL_SCANCODE_UP]) {
                SDL_Log("Launching!");
                // Don't like dynamic casts, but we'll do this for now until we either implement CRTP for entities or go
                // another route; don't want to jump ahead in the course and have to redo a ton of work
                projectile->Launch(static_cast<float>(transformed.getX()),
                                   static_cast<float>(transformed.getY()), -200);
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