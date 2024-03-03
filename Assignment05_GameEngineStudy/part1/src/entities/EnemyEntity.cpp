#include <components/Collision2DComponent.h>
#include <components/TextureComponent.h>
#include <entities/EnemyEntity.h>

EnemyEntity::EnemyEntity() {
    // Set a random launch time for the enemies
    m_MinLaunchTime += std::rand() % 10000;
}

void EnemyEntity::AddRequired(SDL_Renderer* renderer) {
    GameEntity::AddRequired();

    // Add a texture component to our enemy
    std::shared_ptr<TextureComponent> tex = std::make_shared<TextureComponent>();
    tex->CreateTextureComponent(renderer, "../assets/enemy.bmp");
    AddComponent(tex);

    std::shared_ptr<Collision2DComponent> col = std::make_shared<Collision2DComponent>();
    AddComponent(col);

    std::shared_ptr<ProjectileEntity> projectile = std::make_shared<ProjectileEntity>();
    projectile->AddRequired(renderer);
    projectile->GetTransform()->SetW(24.0f);
    AddChild(projectile);
}

void EnemyEntity::Update(float deltaTime) {
    GameEntity::Update(deltaTime);

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
        GetProjectile()->Launch(transform->GetX(), transform->GetY(), 200, m_MinLaunchTime);
    }

    for (auto& [key, value] : m_Components) {
        m_Components[key]->Update(deltaTime);
    }
}

void EnemyEntity::Render(SDL_Renderer* renderer) {
    GameEntity::Render(renderer);

    if (IsRenderable()) {
        GetProjectile()->Render(renderer);
    } else {
        // Do nothing;
        GetProjectile()->SetRenderable(false);
        return;
    }
}

[[nodiscard]] std::shared_ptr<ProjectileEntity> EnemyEntity::GetProjectile() const {
    // Don't like dynamic casts, but we'll do this for now until we either implement CRTP for entities or go another
    // route; don't want to jump ahead in the course and have to redo a ton of work
    return dynamic_pointer_cast<ProjectileEntity>(m_Children[0]);
}