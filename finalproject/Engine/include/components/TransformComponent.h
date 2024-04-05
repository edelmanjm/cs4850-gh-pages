#pragma once
#include <memory>
#include <string>

#include <homog2d.hpp>

#include <components/Component.h>

class TransformComponent : public Component {
public:
    TransformComponent(h2d::FRect rectangle);
    TransformComponent(SDL_FRect rectangle);

    ~TransformComponent() override;

    ComponentType GetType() override;

    void Input(float deltaTime) override;

    void Update(float deltaTime) override;

    void Render(SDL_Renderer* renderer) override;

    /**
     * SDL_FRects must be axis-aligned, while h2d::FRects do not have to be. If the underlying rectangle is
     * axis-aligned, this function returns the corresponding equivalent SDL_FRect. If it is not axis-aligned, then
     * the underlying rectangle cannot be represented as an SDL_FRect, and this returns an empty optional.
     * @return An SDL_FRect, or empty.
     */
    std::optional<SDL_FRect> AsSDL();

    /**
     * Compatibility method.
     * @return The x-coordinate of the top-left of the transformation.
     */
    double GetX() const;

    /**
     * Compatibility method.
     * @return The y-coordinate of the top-left of the transformation.
     */
    double GetY() const;

    /**
     * Compatibility method.
     * @param x The x-coordinate of the top-left of the transformation.
     */
    void SetX(double x);

    /**
     * Compatibility method.
     * @param y The y-coordinate of the top-left of the transformation.
     */
    void SetY(double y);

public:
    h2d::FRect m_Rectangle;
};
