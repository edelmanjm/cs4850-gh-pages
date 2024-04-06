#include <components/TransformComponent.h>

TransformComponent::TransformComponent(h2d::FRect rectangle) : m_Rectangle(rectangle) {}

TransformComponent::TransformComponent(SDL_FRect rectangle) {
    // h2d does not allow zero-width rectangles
    float fudgeFactor = 0.001;
    float fudgedWidth = rectangle.w == 0 ? fudgeFactor : 0;
    float fudgedHeight = rectangle.h == 0 ? fudgeFactor : 0;
    m_Rectangle.set(rectangle.x, rectangle.y, rectangle.x + fudgedWidth, rectangle.y + fudgedHeight);
}

TransformComponent::~TransformComponent() = default;

void TransformComponent::Input(float deltaTime) {}

void TransformComponent::Update(float deltaTime) {}

void TransformComponent::Render(SDL_Renderer* renderer) {}

ComponentType TransformComponent::GetType() { return ComponentType::TransformComponent; }