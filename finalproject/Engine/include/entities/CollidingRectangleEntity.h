#pragma once

#include <entities/GameEntity.h>

class CollidingRectangleEntity : public GameEntity {
public:
    CollidingRectangleEntity();
    void AddRequired(SDL_FRect transform) override;
    void AddInputHandler(std::function<void(float deltaTime, const std::vector<uint8_t> keys)>& onKeypress);

    void Update(float deltaTime) override;

    static bool Intersects(const std::shared_ptr<CollidingRectangleEntity>& foo, const std::shared_ptr<CollidingRectangleEntity>& bar);

public:
    // Eh maybe I'll put this in a struct later
    float m_VelocityX;
    float m_VelocityY;
    // In radians
    float m_Heading;
};