#include <components/Collision2DComponent.h>
#include <components/InputComponent.h>
#include <components/TextureComponent.h>
#include <entities/PlayerGameEntity.h>
#include <entities/ProjectileEntity.h>

#include <algorithm>

PlayerGameEntity::PlayerGameEntity(SDL_Renderer* renderer) {
    m_Projectile = std::make_shared<ProjectileEntity>();
    m_Projectile->AddRequiredComponents(renderer);
    m_Projectile->GetTransform()->SetW(24.0f);
}

void PlayerGameEntity::AddRequiredComponents(SDL_Renderer* renderer, uint32_t screenWidth) {
    GameEntity::AddRequiredComponents();

    std::shared_ptr<TextureComponent> characterTexture = std::make_shared<TextureComponent>();
    characterTexture->CreateTextureComponent(renderer, "../assets/hero.bmp");
    AddComponent(characterTexture);

    std::shared_ptr<InputComponent> inputController =
        std::make_shared<InputComponent>(0, static_cast<float>(screenWidth) - GetTransform()->GetRectangle().w);
    AddComponent(inputController);

    std::shared_ptr<Collision2DComponent> col = std::make_shared<Collision2DComponent>();
    AddComponent(col);
}

void PlayerGameEntity::Update(float deltaTime) {
    m_Projectile->Update(deltaTime);
    GameEntity::Update(deltaTime);
}

void PlayerGameEntity::Render(SDL_Renderer* renderer) {
    m_Projectile->Render(renderer);
    GameEntity::Render(renderer);
}

[[nodiscard]] std::shared_ptr<ProjectileEntity> PlayerGameEntity::GetProjectile() const { return m_Projectile; }