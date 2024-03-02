#include <components/InputComponent.h>
#include <components/TransformComponent.h>
#include <entities/GameEntity.h>

InputComponent::InputComponent() = default;

InputComponent::~InputComponent() = default;

ComponentType InputComponent::GetType() { return ComponentType::InputComponent; }

void InputComponent::Input(float deltaTime) {
    const Uint8* state = SDL_GetKeyboardState(nullptr);
    // For now -- keep a reference to our first sprite
    auto ge = GetGameEntity();
    auto transform = ge->GetComponent<TransformComponent>(ComponentType::TransformComponent).value();

    if (state[SDL_SCANCODE_LEFT]) {
        transform->SetX(transform->GetX() - mSpeed * deltaTime);
        SDL_Log("Did something");
    } else if (state[SDL_SCANCODE_RIGHT]) {
        transform->SetX(transform->GetX() + mSpeed * deltaTime);
    }

    if (state[SDL_SCANCODE_UP]) {
        SDL_Log("Launching!");
        //        mProjectile->Launch(ref->GetX(),ref->GetY(),true);
    }
}

void InputComponent::Update(float deltaTime) {}

void InputComponent::Render(SDL_Renderer* renderer) {}
