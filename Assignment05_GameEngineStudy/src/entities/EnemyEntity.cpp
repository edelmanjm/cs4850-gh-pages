#include <components/Collision2DComponent.h>
#include <components/TextureComponent.h>
#include <entities/EnemyEntity.h>

EnemyEntity::EnemyEntity(SDL_Renderer* renderer) {
    // Create a texture
    std::shared_ptr<TextureComponent> texture = std::make_shared<TextureComponent>();
    texture->CreateTextureComponent(renderer, "../assets/rocket.bmp");
    // Create a collider for our projectile
    std::shared_ptr<Collision2DComponent> col = std::make_shared<Collision2DComponent>();

    m_Projectile = std::make_shared<ProjectileEntity>();
    m_Projectile->GetTransform()->SetW(24.0f);

    m_Projectile->AddComponent(texture);
    m_Projectile->AddComponent(col);

    // Set a random launch time for the enemies
    m_MinLaunchTime += std::rand() % 10000;
}

void EnemyEntity::Input(float deltaTime) {
    for (auto& [key, value] : m_Components) {
        m_Components[key]->Input(deltaTime);
    }
}

void EnemyEntity::Update(float deltaTime) {
    m_Projectile->Update(deltaTime);
    if (m_Offset > 80) {
        m_XPositiveDirection = false;
    }
    if (m_Offset < -80) {
        m_XPositiveDirection = true;
    }

    // Keeping track of our projectile game logic
    auto transform = GetComponent<TransformComponent>(ComponentType::TransformComponent).value();

    if (m_XPositiveDirection) {
        transform->SetX(transform->GetX() + m_Speed * deltaTime);
        m_Offset += m_Speed * deltaTime;
    } else {
        transform->SetX(transform->GetX() - m_Speed * deltaTime);
        m_Offset -= m_Speed * deltaTime;
    }

    if (IsRenderable()) {
        m_Projectile->Launch(transform->GetX(), transform->GetY(), false, m_MinLaunchTime);
    }

    for (auto& [key, value] : m_Components) {
        m_Components[key]->Update(deltaTime);
    }
}

[[nodiscard]] std::shared_ptr<ProjectileEntity> EnemyEntity::GetProjectile() const { return m_Projectile; }