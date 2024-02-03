#include <entities/EnemyEntity.h>

EnemyEntity::EnemyEntity(SDL_Renderer *renderer, Sprite sprite) : GameEntity(sprite) {
    Sprite sp;
    sp.CreateSprite(renderer, "../assets/rocket.bmp");
    sp.SetW(24.0f);
    m_Projectile = std::make_shared<ProjectileEntity>(sp);

    // Set a random launch time for the m_Enemies
    m_MinLaunchTime += std::rand() % 10000;
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
        m_Sprite.SetX(m_Sprite.GetX() + m_Speed * deltaTime);
        m_Offset += m_Speed * deltaTime;
    } else {
        m_Sprite.SetX(m_Sprite.GetX() - m_Speed * deltaTime);
        m_Offset -= m_Speed * deltaTime;
    }

    if (m_Renderable) {
        m_Projectile->Launch(m_Sprite.GetX(), m_Sprite.GetY(), false, m_MinLaunchTime);
    }
}

void EnemyEntity::Render(SDL_Renderer *renderer) {
    if (m_Renderable) {
        m_Projectile->Render(renderer);
        m_Sprite.Render(renderer);
    } else {
        // Do nothing;
    }
}

[[nodiscard]] std::shared_ptr<ProjectileEntity> EnemyEntity::GetProjectile() const {
    return m_Projectile;
}