#include <entities/EnemyEntity.h>

EnemyEntity::EnemyEntity(SDL_Renderer *renderer, std::shared_ptr<Sprite> sprite) : GameEntity(sprite) {
    std::shared_ptr<Sprite> sp = std::make_shared<Sprite>();
    sp->CreateSprite(renderer, "../assets/rocket.bmp");
    sp->SetW(24.0f);
    m_Projectile = std::make_shared<ProjectileEntity>(sp);

    // Set a random launch time for the m_Enemies
    m_MinLaunchTime += std::rand() % 10000;

    m_Components.push_back(sp);
}

void EnemyEntity::Input(float deltaTime) {
}

void EnemyEntity::Update(float deltaTime) {
    m_Projectile->Update(deltaTime);
    if (m_Offset > 80) {
        m_XPositiveDirection = false;
    }
    if (m_Offset < -80) {
        m_XPositiveDirection = true;
    }

    if (m_XPositiveDirection) {
        m_Sprite->SetX(m_Sprite->GetX() + m_Speed * deltaTime);
        m_Offset += m_Speed * deltaTime;
    } else {
        m_Sprite->SetX(m_Sprite->GetX() - m_Speed * deltaTime);
        m_Offset -= m_Speed * deltaTime;
    }

    if (m_Sprite->m_Renderable) {
        m_Projectile->Launch(m_Sprite->GetX(), m_Sprite->GetY(), false, m_MinLaunchTime);
    }
}

[[nodiscard]] std::shared_ptr<ProjectileEntity> EnemyEntity::GetProjectile() const {
    return m_Projectile;
}