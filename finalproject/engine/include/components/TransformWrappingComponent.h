#pragma once

#include <homog2d.hpp>

#include <components/Component.h>

/**
 * A component that makes it so when the transform exceeds the bounds specified, it wraps to the other side.
 */
class TransformWrappingComponent : public Component {
public:
    TransformWrappingComponent(h2d::FRect bounds);

    ~TransformWrappingComponent() override;

    ComponentType GetType() override;

    void Input(float deltaTime) override;

    void Update(float deltaTime) override;

    void Render(SDL_Renderer* renderer) override;

private:
    h2d::FRect m_Bounds;
};