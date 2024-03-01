#pragma once

#include <SDL3/SDL.h>

#include <entities/ProjectileEntity.h>

class PlayerGameEntity : public GameEntity {

private:
    float m_Speed{150.0f};
    const float m_XMin;
    const float m_XMax;
    std::shared_ptr<ProjectileEntity> m_Projectile;

public:
    PlayerGameEntity(SDL_Renderer *renderer, std::shared_ptr<Sprite> sprite, float xMin, float xMax);

    ~PlayerGameEntity() override = default;

    void Input(float deltaTime) override;

    void Update(float deltaTime) override;

    [[nodiscard]] virtual std::shared_ptr<ProjectileEntity> GetProjectile() const;
};