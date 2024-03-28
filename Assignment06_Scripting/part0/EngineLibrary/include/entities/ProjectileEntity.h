#pragma once

#include <entities/GameEntity.h>

class ProjectileEntity : public GameEntity {

private:
    float m_Speed{0.0};
    bool m_IsFiring{false};
    uint64_t timeSinceLastLaunch;

public:
    explicit ProjectileEntity();
    void AddRequired(SDL_FRect transform, SDL_Renderer* renderer);

    void Launch(float x, float y, float speed, uint64_t minLaunchTime = 3000);
    void Input(float deltaTime) override;
    void Update(float deltaTime) override;
};