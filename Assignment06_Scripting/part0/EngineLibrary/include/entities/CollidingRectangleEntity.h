#pragma once

#include <entities/GameEntity.h>

class CollidingRectangleEntity : public GameEntity {
public:
    CollidingRectangleEntity();
    void AddRequired(SDL_FRect transform) override;

    void SetPosition(SDL_FRect transform);
    void SetVelocity(float x, float y);
    void Update(float deltaTime) override;

    static bool Intersects(std::shared_ptr<CollidingRectangleEntity> foo, std::shared_ptr<CollidingRectangleEntity> bar);

private:
    // Eh maybe I'll put this in a struct later
    float m_VelocityX;
    float m_VelocityY;
};