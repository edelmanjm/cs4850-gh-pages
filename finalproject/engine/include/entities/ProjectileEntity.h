#pragma once

#include <entities/GameEntity.h>

class ProjectileEntity : public GameEntity {

private:
    double m_Speed{0.0};
    bool m_IsFiring{false};
    uint64_t timeSinceLastLaunch;

public:
    explicit ProjectileEntity();
    void AddRequired(h2d::FRect dims, SDL_Renderer* renderer);

    void Launch(float x, float y, float speed, uint64_t minLaunchTime = 3000);
    void Input(float deltaTime) override;
    void Update(float deltaTime) override;
};