#pragma once

// Wrapper for use with pybind11

#include <SDL3/SDL.h>

class Renderer {
public:
    Renderer(int w, int h);

    SDL_Renderer* m_Wrapped;
};