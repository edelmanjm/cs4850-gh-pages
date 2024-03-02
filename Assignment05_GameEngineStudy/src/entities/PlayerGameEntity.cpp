#include <components/Collision2DComponent.h>
#include <components/TextureComponent.h>
#include <entities/PlayerGameEntity.h>
#include <entities/ProjectileEntity.h>

#include <algorithm>

#include <iostream>

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

void PlayerGameEntity::Update(float deltaTime) {
    m_Projectile->Update(deltaTime);
    for (auto& [key, value] : m_Components) {
        m_Components[key]->Update(deltaTime);
    }
    std::cout << m_Projectile->GetTransform()->GetRectangle().y << std::endl;
}

void PlayerGameEntity::Render(SDL_Renderer* renderer){
    m_Projectile->Render(renderer);
    GameEntity::Render(renderer);
}

[[nodiscard]] std::shared_ptr<ProjectileEntity> PlayerGameEntity::GetProjectile() const { return m_Projectile; }