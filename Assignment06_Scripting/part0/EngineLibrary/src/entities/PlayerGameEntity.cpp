#include <components/Collision2DComponent.h>
#include <components/InputComponent.h>
#include <components/TextureComponent.h>
#include <entities/PlayerGameEntity.h>
#include <entities/ProjectileEntity.h>

#include <algorithm>

PlayerGameEntity::PlayerGameEntity() = default;

void PlayerGameEntity::AddRequired(SDL_FRect transform, SDL_Renderer* renderer, uint32_t screenWidth) {
    GameEntity::AddRequired(transform);

    std::shared_ptr<TextureComponent> characterTexture = std::make_shared<TextureComponent>();
    characterTexture->CreateTextureComponent(renderer, "../assets/hero.bmp");
    AddComponent(characterTexture);

    std::shared_ptr<InputComponent> inputController =
        std::make_shared<InputComponent>(0, static_cast<float>(screenWidth) - GetTransform()->m_Rectangle.w);
    AddComponent(inputController);

    std::shared_ptr<Collision2DComponent> col = std::make_shared<Collision2DComponent>();
    AddComponent(col);

    std::shared_ptr<ProjectileEntity> projectile = std::make_shared<ProjectileEntity>();
    projectile->AddRequired(transform, renderer);
    projectile->GetTransform()->m_Rectangle.w = 24.0f;
    AddChild(projectile);
}

[[nodiscard]] std::shared_ptr<ProjectileEntity> PlayerGameEntity::GetProjectile() const {
    // Don't like dynamic casts, but we'll do this for now until we either implement CRTP for entities or go another
    // route; don't want to jump ahead in the course and have to redo a ton of work
    return dynamic_pointer_cast<ProjectileEntity>(m_Children[0]);
}