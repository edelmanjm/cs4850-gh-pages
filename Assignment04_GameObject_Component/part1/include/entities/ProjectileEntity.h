#pragma once

#include <entities/GameEntity.h>

class ProjectileEntity : public GameEntity {

private:
    float m_Speed{200.0f};
    bool m_IsFiring{false};
    bool m_YDirectionUp{true};
    uint64_t timeSinceLastLaunch;

public:
    explicit ProjectileEntity(std::shared_ptr<Sprite> sprite);

    void Launch(float x, float y, bool yDirectionIsUp, uint64_t minLaunchTime = 3000);

    void Update(float deltaTime) override;
};