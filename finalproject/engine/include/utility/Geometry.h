#pragma once

#include <SDL.h>
#include <homog2d.hpp>

/**
 * Various wrappers around and translations between {@link SDL_FRect} and h2d's stuff.
 */
class Geometry {

public:
    static SDL_FRect AsSDL(h2d::FRect r);

    static h2d::FRect AsH2D(SDL_FRect r);

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

    /**
     * Calculate the rotation that this transformation applies
     * @param transform The transform to extract the rotation from.
     * @return The rotation, in radians.
     */
    static double ApproximateRotation(h2d::Homogr transform);

};