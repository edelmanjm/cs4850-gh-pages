#pragma once

#include <SDL3/SDL.h>

/**
 * Wrapper for use with pybind11. Not needed otherwise.
 */
class Renderer {
public:
    Renderer(int w, int h);

    SDL_Renderer* m_Wrapped;
};