#pragma once

#include <SDL3/SDL.h>

#include <entities/ProjectileEntity.h>

class PlayerGameEntity : public GameEntity {
private:
//    float m_Speed{150.0f};
//    const float m_XMin;
//    const float m_XMax;
    std::shared_ptr<ProjectileEntity> m_Projectile;

public:
//    PlayerGameEntity(SDL_Renderer* renderer, float xMin, float xMax);
    PlayerGameEntity(SDL_Renderer* renderer);
    ~PlayerGameEntity() override = default;
    void AddRequiredComponents(SDL_Renderer* renderer);

    void Update(float deltaTime) override;
    void Render(SDL_Renderer* renderer) override;

    [[nodiscard]] virtual std::shared_ptr<ProjectileEntity> GetProjectile() const;
};