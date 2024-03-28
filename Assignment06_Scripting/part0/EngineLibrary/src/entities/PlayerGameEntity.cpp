#include <components/Collision2DComponent.h>
#include <components/InputComponent.h>
#include <components/TextureComponent.h>
#include <entities/PlayerGameEntity.h>
#include <entities/ProjectileEntity.h>

#include <algorithm>

PlayerGameEntity::PlayerGameEntity() = default;

void PlayerGameEntity::AddRequired(SDL_FRect transform, SDL_Renderer* renderer, uint32_t screenWidth) {
    GameEntity::AddRequired(transform);

    m_XMax = static_cast<float>(screenWidth) - GetTransform()->m_Rectangle.w;

    std::shared_ptr<TextureComponent> characterTexture = std::make_shared<TextureComponent>();
    characterTexture->CreateTextureComponent(renderer, "../assets/hero.bmp");
    AddComponent(characterTexture);

    std::shared_ptr<Collision2DComponent> col = std::make_shared<Collision2DComponent>();
    AddComponent(col);

    std::shared_ptr<ProjectileEntity> projectile = std::make_shared<ProjectileEntity>();
    projectile->AddRequired(transform, renderer);
    projectile->GetTransform()->m_Rectangle.w = 24.0f;
    AddChild(projectile);

    std::shared_ptr<InputComponent> inputController =
        std::make_shared<InputComponent>();
    std::function<void(float, const Uint8*)> test =
        [inputController, projectile, this](float deltaTime, const Uint8* state) {
        // For now -- keep a reference to our first sprite
        auto ge = inputController->GetGameEntity();
        auto transform = ge->GetComponent<TransformComponent>(ComponentType::TransformComponent).value();

        if (state[SDL_SCANCODE_LEFT]) {
            transform->m_Rectangle.x = std::max(m_XMin, transform->m_Rectangle.x - m_Speed * deltaTime);
        } else if (state[SDL_SCANCODE_RIGHT]) {
            transform->m_Rectangle.x = std::min(m_XMax, transform->m_Rectangle.x + m_Speed * deltaTime);
        }

        if (state[SDL_SCANCODE_UP]) {
            SDL_Log("Launching!");
            // Don't like dynamic casts, but we'll do this for now until we either implement CRTP for entities or go another
            // route; don't want to jump ahead in the course and have to redo a ton of work
            projectile->Launch(transform->m_Rectangle.x, transform->m_Rectangle.y, -200);
        }
    };
    inputController->SetOnKeypress(test);
    AddComponent(inputController);
}

[[nodiscard]] std::shared_ptr<ProjectileEntity> PlayerGameEntity::GetProjectile() const {
    // Don't like dynamic casts, but we'll do this for now until we either implement CRTP for entities or go another
    // route; don't want to jump ahead in the course and have to redo a ton of work
    return dynamic_pointer_cast<ProjectileEntity>(m_Children[0]);
}