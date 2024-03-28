#include <entities/CollidingRectangleEntity.h>
#include <components/Collision2DComponent.h>


CollidingRectangleEntity::CollidingRectangleEntity() {
    SetRenderable(true);
}

void CollidingRectangleEntity::AddRequired(SDL_FRect transform) {
    GameEntity::AddRequired(transform);

    auto c = std::make_shared<Collision2DComponent>(true);
    AddComponent<Collision2DComponent>(c);
}

void CollidingRectangleEntity::SetVelocity(float x, float y) {
    m_VelocityX = x;
    m_VelocityY = y;
}

void CollidingRectangleEntity::Update(float deltaTime) {
    auto transform = GetComponent<TransformComponent>(ComponentType::TransformComponent).value();

    transform->m_Rectangle.x = transform->m_Rectangle.x + m_VelocityX * deltaTime;
    transform->m_Rectangle.y = transform->m_Rectangle.y + m_VelocityY * deltaTime;

    for (auto &[key, value]: m_Components) {
        m_Components[key]->Update(deltaTime);
    }
}