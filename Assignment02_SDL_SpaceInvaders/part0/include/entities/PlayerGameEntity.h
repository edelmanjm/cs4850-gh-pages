#pragma once

#include <SDL3/SDL.h>

#include <entities/ProjectileEntity.h>

class PlayerGameEntity : public GameEntity {

private:
    float m_Speed{150.0f};
    std::shared_ptr<ProjectileEntity> m_Projectile;

public:
    PlayerGameEntity(SDL_Renderer *renderer, Sprite sprite);

    ~PlayerGameEntity() override = default;

    void Input(float deltaTime) override;

    void Update(float deltaTime) override;

    void Render(SDL_Renderer *renderer) override;

    [[nodiscard]] virtual std::shared_ptr<ProjectileEntity> GetProjectile() const;
};