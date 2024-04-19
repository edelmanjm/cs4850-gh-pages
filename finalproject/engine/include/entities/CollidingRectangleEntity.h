#pragma once

#include <entities/GameEntity.h>

class CollidingRectangleEntity : public GameEntity {
public:
    CollidingRectangleEntity();
    void AddRequired(h2d::FRect dims, bool showBoundingBox = true);
    void AddInputHandler(std::function<void(float deltaTime, const std::vector<uint8_t> keys)>& onKeypress);

    void Update(float deltaTime) override;

    void Rotate(float rads);
    float GetRotation();

    static bool Intersects(const std::shared_ptr<CollidingRectangleEntity>& foo, const std::shared_ptr<CollidingRectangleEntity>& bar);
    static bool IntersectsFRect(const std::shared_ptr<CollidingRectangleEntity>& foo, h2d::FRect bar);

public:
    // Eh maybe I'll put this in a struct later
    float m_VelocityX = 0;
    float m_VelocityY = 0;

private:
    // In rads
    float m_Rotation = 0;
};