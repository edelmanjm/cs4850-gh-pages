#pragma once

#include <SDL3/SDL.h>
#include <memory>
#include <string>

#include <components/Component.h>

class InputComponent : public Component {
public:
    InputComponent();

    ~InputComponent() override;

    ComponentType GetType() override;

    void Input(float deltaTime) override;

    void Update(float deltaTime) override;

    void Render(SDL_Renderer* renderer) override;

    void SetOnKeypress(std::function<void(float deltaTime, const std::vector<uint8_t> keys)>& onKeypress);

private:
    std::function<void(float deltaTime, const std::vector<uint8_t> keys)> m_OnKeypress;
};
