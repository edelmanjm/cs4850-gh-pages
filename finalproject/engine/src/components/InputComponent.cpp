#include <components/InputComponent.h>
#include <components/TransformComponent.h>
#include <entities/ProjectileEntity.h>

InputComponent::InputComponent() {}

InputComponent::~InputComponent() = default;

ComponentType InputComponent::GetType() { return ComponentType::InputComponent; }

void InputComponent::Input(float deltaTime) {
    int numkeys;
    const Uint8* state = SDL_GetKeyboardState(&numkeys);
    std::vector<uint8_t> keys(state, state + numkeys);
    m_OnKeypress(deltaTime, keys);
}

void InputComponent::Update(float deltaTime) {}

void InputComponent::Render(SDL_Renderer* renderer) {}

void InputComponent::SetOnKeypress(std::function<void(float deltaTime, const std::vector<uint8_t> keys)>&
    onKeypress) {
    m_OnKeypress = std::move(onKeypress);
}