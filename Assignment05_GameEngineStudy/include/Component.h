#pragma once

#include <SDL3/SDL.h>

class Component {
public:
    Component() = default;
    ~Component() = default;

    virtual void Input(float deltaTime) = 0;

    virtual void Update(float deltaTime) = 0;

    virtual void Render(SDL_Renderer *renderer) = 0;
};
