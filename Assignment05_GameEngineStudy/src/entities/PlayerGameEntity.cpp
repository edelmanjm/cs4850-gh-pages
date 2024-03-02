#include <components/Collision2DComponent.h>
#include <components/InputComponent.h>
#include <components/TextureComponent.h>
#include <entities/PlayerGameEntity.h>
#include <entities/ProjectileEntity.h>

#include <algorithm>

//PlayerGameEntity::PlayerGameEntity(SDL_Renderer* renderer, float xMin, float xMax)
PlayerGameEntity::PlayerGameEntity(SDL_Renderer* renderer) {
//    , m_XMin(xMin)
//    , m_XMax(xMax) {
    m_Projectile = std::make_shared<ProjectileEntity>();
    m_Projectile->AddRequiredComponents(renderer);
    m_Projectile->GetTransform()->SetW(24.0f);
}

void PlayerGameEntity::AddRequiredComponents(SDL_Renderer* renderer) {
    GameEntity::AddRequiredComponents();

    std::shared_ptr<TextureComponent> characterTexture = std::make_shared<TextureComponent>();
    characterTexture->CreateTextureComponent(renderer, "../assets/hero.bmp");
    AddComponent(characterTexture);

    std::shared_ptr<InputComponent> inputController = std::make_shared<InputComponent>();
    AddComponent(inputController);

    std::shared_ptr<Collision2DComponent> col = std::make_shared<Collision2DComponent>();
    AddComponent(col);
}

void PlayerGameEntity::Update(float deltaTime) {
    m_Projectile->Update(deltaTime);
    GameEntity::Update(deltaTime);
}

void PlayerGameEntity::Render(SDL_Renderer* renderer){
    m_Projectile->Render(renderer);
    GameEntity::Render(renderer);
}

[[nodiscard]] std::shared_ptr<ProjectileEntity> PlayerGameEntity::GetProjectile() const { return m_Projectile; }