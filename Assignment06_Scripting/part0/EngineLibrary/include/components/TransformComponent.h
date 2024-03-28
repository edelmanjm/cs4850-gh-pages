#pragma once
#include <SDL3/SDL.h>
#include <memory>
#include <string>

#include <components/Component.h>

class TransformComponent : public Component {
public:
    TransformComponent(SDL_FRect rectangle);

    ~TransformComponent() override;

    ComponentType GetType() override;

    void Input(float deltaTime) override;

    void Update(float deltaTime) override;

    void Render(SDL_Renderer* renderer) override;

public:
    SDL_FRect m_Rectangle;
};
