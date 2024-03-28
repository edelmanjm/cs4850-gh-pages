#include <components/InputComponent.h>
#include <components/TransformComponent.h>
#include <entities/ProjectileEntity.h>

InputComponent::InputComponent() {}

InputComponent::~InputComponent() = default;

ComponentType InputComponent::GetType() { return ComponentType::InputComponent; }

void InputComponent::Input(float deltaTime) {
    const Uint8* state = SDL_GetKeyboardState(nullptr);
    m_OnKeypress(deltaTime, state);
}

void InputComponent::Update(float deltaTime) {}

void InputComponent::Render(SDL_Renderer* renderer) {}

void InputComponent::SetOnKeypress(std::function<void(float deltaTime, const Uint8* keypress)>& onKeypress) {
    m_OnKeypress = std::move(onKeypress);
}