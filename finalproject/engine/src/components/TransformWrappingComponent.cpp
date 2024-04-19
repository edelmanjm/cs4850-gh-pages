#include <algorithm>

#include <SDL3/SDL.h>

#include <components/TransformWrappingComponent.h>
#include <entities/GameEntity.h>

TransformWrappingComponent::TransformWrappingComponent(h2d::FRect bounds) : m_Bounds(bounds) {}
TransformWrappingComponent::~TransformWrappingComponent() = default;

void TransformWrappingComponent::Input(float deltaTime) {}

void TransformWrappingComponent::Update(float deltaTime) {
    auto ge = GetGameEntity();
    auto& transform = ge->GetTransform()->m_Transform;
    auto offset = ge->GetTransformedOrigin();

    if (offset.getX() < 0) {
        transform.addTranslation(m_Bounds.width(), 0.0);
    } else if (offset.getX() > m_Bounds.width()) {
        transform.addTranslation(-m_Bounds.width(), 0.0);
    }
    if (offset.getY() < 0) {
        transform.addTranslation(0.0, m_Bounds.height());
    } else if (offset.getY() > m_Bounds.height()) {
        transform.addTranslation(0.0, -m_Bounds.height());
    }
}

void TransformWrappingComponent::Render(SDL_Renderer* renderer) {}

ComponentType TransformWrappingComponent::GetType() { return ComponentType::TransformWrappingComponent; }