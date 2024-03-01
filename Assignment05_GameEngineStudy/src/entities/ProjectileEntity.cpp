#include <entities/ProjectileEntity.h>

ProjectileEntity::ProjectileEntity(std::shared_ptr<Sprite> sprite) : GameEntity(sprite) {
    timeSinceLastLaunch = SDL_GetTicks();
    m_Sprite->m_Renderable = false;
}

void ProjectileEntity::Launch(float x, float y, bool yDirectionIsUp, uint64_t minLaunchTime) {
    if (SDL_GetTicks() - timeSinceLastLaunch > minLaunchTime) {
        timeSinceLastLaunch = SDL_GetTicks();
        m_IsFiring = true;
        m_YDirectionUp = yDirectionIsUp;
        m_Sprite->Move(x, y);
    }
}

void ProjectileEntity::Update(float deltaTime) {
    if (m_IsFiring) {
        m_Sprite->m_Renderable = true;
        if (m_YDirectionUp) {
            m_Sprite->SetY(m_Sprite->GetY() - m_Speed * deltaTime);
        } else {
            m_Sprite->SetY(m_Sprite->GetY() + m_Speed * deltaTime);
        }
    } else {
        m_Sprite->m_Renderable = false;
    }

    if (m_Sprite->GetY() < 0.0f || m_Speed > 480.0f) {
        m_IsFiring = false;
    }
}