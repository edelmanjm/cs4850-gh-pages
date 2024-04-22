#pragma once
#include <memory>
#include <string>

#include <SDL3/SDL.h>
#include <homog2d.hpp>

#include <components/Component.h>

/**
 * A component backed by a rectangular bounding box. Useful for when you want to check for intersections with other
 * {@link Collision2DComponent}s or {@link h2d::FRect}.
 */
class Collision2DComponent : public Component {
public:
    Collision2DComponent(h2d::FRect box, bool showBoundingBox = false);

    ~Collision2DComponent() override;

    ComponentType GetType() override;

    void Input(float deltaTime) override;

    void Update(float deltaTime) override;

    void Render(SDL_Renderer* renderer) override;

    static bool Intersects(const std::shared_ptr<Collision2DComponent>& foo, std::shared_ptr<Collision2DComponent> bar);
    static bool IntersectsFRect(const std::shared_ptr<Collision2DComponent>& foo, h2d::FRect bar);

private:
    h2d::CPolyline getCollisionQuad();

private:
    h2d::FRect m_Box;

    bool m_ShowBoundingBox;
};
