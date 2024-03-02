#include <components/Collision2DComponent.h>
#include <components/TextureComponent.h>
#include <entities/PlayerGameEntity.h>
#include <entities/ProjectileEntity.h>

#include <algorithm>

//PlayerGameEntity::PlayerGameEntity(SDL_Renderer* renderer, float xMin, float xMax)
PlayerGameEntity::PlayerGameEntity(SDL_Renderer* renderer) {
//    , m_XMin(xMin)
//    , m_XMax(xMax) {
    std::shared_ptr<TextureComponent> texture = std::make_shared<TextureComponent>();
    texture->CreateTextureComponent(renderer, "../assets/rocket.bmp");

    std::shared_ptr<Collision2DComponent> col = std::make_shared<Collision2DComponent>();

    m_Projectile = std::make_shared<ProjectileEntity>();
    m_Projectile->GetTransform()->SetW(24.0f);

    m_Projectile->AddComponent(texture);
    m_Projectile->AddComponent(col);
}

void PlayerGameEntity::Input(float deltaTime) {
    for (auto& [key, value] : m_Components) {
        m_Components[key]->Input(deltaTime);
    }
}

void PlayerGameEntity::Update(float deltaTime) {
    m_Projectile->Update(deltaTime);
    for (auto& [key, value] : m_Components) {
        m_Components[key]->Update(deltaTime);
    }
}

[[nodiscard]] std::shared_ptr<ProjectileEntity> PlayerGameEntity::GetProjectile() const { return m_Projectile; }