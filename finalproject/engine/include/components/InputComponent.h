#pragma once

#include <SDL3/SDL.h>
#include <memory>
#include <string>

#include <components/Component.h>

/**
 * An input component is used to handle inputs by forwarding them to an on-keypress function, which can do whatever
 * is required. Typically, this is used to allow Python to interface with C++ via an anonymous function.
 */
class InputComponent : public Component {
public:
    InputComponent();

    ~InputComponent() override;

    ComponentType GetType() override;

    void Input(float deltaTime) override;

    void Update(float deltaTime) override;

    void Render(SDL_Renderer* renderer) override;

    /**
     * Sets the function to be called when an input is received.
     * @param onKeypress The function that should be called by {@link InputComponent::Input}.
     */
    void SetOnKeypress(std::function<void(float deltaTime, const std::vector<uint8_t> keys)>& onKeypress);

private:
    std::function<void(float deltaTime, const std::vector<uint8_t> keys)> m_OnKeypress;
};
