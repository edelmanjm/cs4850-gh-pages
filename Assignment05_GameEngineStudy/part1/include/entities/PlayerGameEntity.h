#pragma once

#include <SDL3/SDL.h>

#include <entities/ProjectileEntity.h>

class PlayerGameEntity : public GameEntity {
public:
    PlayerGameEntity();
    ~PlayerGameEntity() override = default;
    void AddRequired(SDL_Renderer* renderer, uint32_t screenWidth);

    [[nodiscard]] virtual std::shared_ptr<ProjectileEntity> GetProjectile() const;
};