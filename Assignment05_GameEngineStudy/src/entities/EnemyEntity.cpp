#include <components/Collision2DComponent.h>
#include <components/TextureComponent.h>
#include <entities/EnemyEntity.h>

EnemyEntity::EnemyEntity(SDL_Renderer* renderer) {
    m_Projectile = std::make_shared<ProjectileEntity>();
    m_Projectile->AddRequiredComponents(renderer);
    m_Projectile->GetTransform()->SetW(24.0f);

    // Set a random launch time for the enemies
    m_MinLaunchTime += std::rand() % 10000;
}

void EnemyEntity::AddRequiredComponents(SDL_Renderer* renderer) {
    GameEntity::AddRequiredComponents();

    // Add a texture component to our enemy
    std::shared_ptr<TextureComponent> tex = std::make_shared<TextureComponent>();
    tex->CreateTextureComponent(renderer, "../assets/enemy.bmp");
    AddComponent(tex);

    std::shared_ptr<Collision2DComponent> col = std::make_shared<Collision2DComponent>();
    AddComponent(col);
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

void EnemyEntity::Render(SDL_Renderer* renderer) {
    if (IsRenderable()) {
        m_Projectile->Render(renderer);
    } else {
        // Do nothing;
        m_Projectile->SetRenderable(false);
        return;
    }
    GameEntity::Render(renderer);
}

[[nodiscard]] std::shared_ptr<ProjectileEntity> EnemyEntity::GetProjectile() const { return m_Projectile; }