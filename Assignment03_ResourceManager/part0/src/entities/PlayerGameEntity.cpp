#include <entities/PlayerGameEntity.h>

#include <algorithm>

PlayerGameEntity::PlayerGameEntity(SDL_Renderer *renderer, Sprite sprite, float xMin, float xMax) : GameEntity
(sprite), m_XMin(xMin), m_XMax(xMax) {
    Sprite sp;
    sp.CreateSprite(renderer, "../assets/rocket.bmp");
    sp.SetW(24.0f);
    m_Projectile = std::make_shared<ProjectileEntity>(sp);
}

void PlayerGameEntity::Input(float deltaTime)  {
    const Uint8 *state = SDL_GetKeyboardState(nullptr);
    if (state[SDL_SCANCODE_LEFT]) {
        m_Sprite.SetX(std::max(m_Sprite.GetX() - m_Speed * deltaTime, m_XMin));
    } else if (state[SDL_SCANCODE_RIGHT]) {
        m_Sprite.SetX(std::min(m_Sprite.GetX() + m_Speed * deltaTime, m_XMax));
    }

    if (state[SDL_SCANCODE_UP]) {
        SDL_Log("Launching!");
        m_Projectile->Launch(m_Sprite.GetX(), m_Sprite.GetY(), true);
    }
}

void PlayerGameEntity::Update(float deltaTime) {
    m_Projectile->Update(deltaTime);
}

void PlayerGameEntity::Render(SDL_Renderer *renderer) {
    m_Projectile->Render(renderer);
    m_Sprite.Render(renderer);
}

[[nodiscard]] std::shared_ptr<ProjectileEntity> PlayerGameEntity::GetProjectile() const {
    return m_Projectile;
}