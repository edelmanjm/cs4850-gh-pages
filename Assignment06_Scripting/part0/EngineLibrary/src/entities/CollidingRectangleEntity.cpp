#include <entities/CollidingRectangleEntity.h>
#include "components/Collision2DComponent.h"


CollidingRectangleEntity::CollidingRectangleEntity() {
    SetRenderable(true);
}

void CollidingRectangleEntity::AddRequired() {
    GameEntity::AddRequired();

    auto c = std::make_shared<Collision2DComponent>(true);
    auto t = std::make_shared<TransformComponent>();

    AddComponent<Collision2DComponent>(c);
}

void CollidingRectangleEntity::SetVelocity(float x, float y) {
    m_VelocityX = x;
    m_VelocityY = y;
}

void CollidingRectangleEntity::Update(float deltaTime) {
    auto transform = GetComponent<TransformComponent>(ComponentType::TransformComponent).value();

    transform->SetX(transform->GetX() + m_VelocityX * deltaTime);
    transform->SetY(transform->GetY() + m_VelocityY * deltaTime);

    for (auto &[key, value]: m_Components) {
        m_Components[key]->Update(deltaTime);
    }
}