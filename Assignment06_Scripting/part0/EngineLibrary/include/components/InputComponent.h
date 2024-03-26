#pragma once

#include <SDL3/SDL.h>
#include <memory>
#include <string>

#include <components/Component.h>

class InputComponent : public Component {
public:
    InputComponent(float xMin, float xMax);

    ~InputComponent() override;

    ComponentType GetType() override;

    void Input(float deltaTime) override;

    void Update(float deltaTime) override;

    void Render(SDL_Renderer* renderer) override;

private:
    const float m_Speed{150};
    const float m_XMin;
    const float m_XMax;
};
