#pragma once

#include <SDL.h>
#include <homog2d.hpp>

class Geometry {

public:
    /**
     * SDL_FRects must be axis-aligned, while h2d::FRects do not have to be. If the underlying rectangle is
     * axis-aligned, this function returns the corresponding equivalent SDL_FRect. If it is not axis-aligned, then
     * the underlying rectangle cannot be represented as an SDL_FRect, and this returns an empty optional.
     * @return An SDL_FRect, or empty.
     */
    static std::optional<SDL_FRect> AsSDL(h2d::FRect& r);

    /**
     * Compatibility method.
     * @return The x-coordinate of the top-left of the transformation.
     */
    static double GetX(h2d::FRect& r);

    /**
     * Compatibility method.
     * @return The y-coordinate of the top-left of the transformation.
     */
    static double GetY(h2d::FRect& r);

    /**
     * Compatibility method.
     * @param x The x-coordinate of the top-left of the transformation.
     */
    static void SetX(h2d::FRect& r, double x);

    /**
     * Compatibility method.
     * @param y The y-coordinate of the top-left of the transformation.
     */
    static void SetY(h2d::FRect& r, double y);

};