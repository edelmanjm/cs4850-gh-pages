#pragma once

#include <entities/GameEntity.h>

class ProjectileEntity : public GameEntity {

private:
    float m_Speed{200.0f};
    bool m_IsFiring{false};
    uint64_t timeSinceLastLaunch;


public:
    explicit ProjectileEntity();
    void AddRequiredComponents(SDL_Renderer* renderer);

    void Launch(float x, float y, bool yDirectionIsUp, uint64_t minLaunchTime = 3000);
    void Input(float deltaTime) override;
    void Update(float deltaTime) override;
};