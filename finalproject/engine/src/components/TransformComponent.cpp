#include <components/TransformComponent.h>

TransformComponent::TransformComponent() = default;
TransformComponent::~TransformComponent() = default;

void TransformComponent::Input(float deltaTime) {}

void TransformComponent::Update(float deltaTime) {}

void TransformComponent::Render(SDL_Renderer* renderer) {}

ComponentType TransformComponent::GetType() { return ComponentType::TransformComponent; }