#include <components/InputComponent.h>
#include <components/TransformComponent.h>
#include <entities/ProjectileEntity.h>

InputComponent::InputComponent(float xMin, float xMax) : m_XMin(xMin), m_XMax(xMax) {}

InputComponent::~InputComponent() = default;

ComponentType InputComponent::GetType() { return ComponentType::InputComponent; }

void InputComponent::Input(float deltaTime) {
    const Uint8* state = SDL_GetKeyboardState(nullptr);
    // For now -- keep a reference to our first sprite
    auto ge = GetGameEntity();
    auto transform = ge->GetComponent<TransformComponent>(ComponentType::TransformComponent).value();

    if (state[SDL_SCANCODE_LEFT]) {
        transform->m_Rectangle.x = std::max(m_XMin, transform->m_Rectangle.x - m_Speed * deltaTime);
    } else if (state[SDL_SCANCODE_RIGHT]) {
        transform->m_Rectangle.x = std::min(m_XMax, transform->m_Rectangle.x + m_Speed * deltaTime);
    }

    if (state[SDL_SCANCODE_UP]) {
        SDL_Log("Launching!");
        // Don't like dynamic casts, but we'll do this for now until we either implement CRTP for entities or go another
        // route; don't want to jump ahead in the course and have to redo a ton of work
        std::shared_ptr<ProjectileEntity> projectile = dynamic_pointer_cast<ProjectileEntity>(ge->GetChildAtIndex(0));
        projectile->Launch(transform->m_Rectangle.x, transform->m_Rectangle.y, -200);
    }
}

void InputComponent::Update(float deltaTime) {}

void InputComponent::Render(SDL_Renderer* renderer) {}
