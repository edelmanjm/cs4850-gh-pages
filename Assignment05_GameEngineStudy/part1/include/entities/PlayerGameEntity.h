#pragma once

#include <SDL3/SDL.h>

#include <entities/ProjectileEntity.h>

class PlayerGameEntity : public GameEntity {
private:
    std::shared_ptr<ProjectileEntity> m_Projectile;

public:
//    PlayerGameEntity(SDL_Renderer* renderer, float xMin, float xMax);
    PlayerGameEntity(SDL_Renderer* renderer);
    ~PlayerGameEntity() override = default;
    void AddRequiredComponents(SDL_Renderer* renderer, uint32_t screenWidth);

    void Update(float deltaTime) override;
    void Render(SDL_Renderer* renderer) override;

    [[nodiscard]] virtual std::shared_ptr<ProjectileEntity> GetProjectile() const;
};