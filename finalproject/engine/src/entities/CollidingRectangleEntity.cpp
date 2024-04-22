#include <components/Collision2DComponent.h>
#include <components/InputComponent.h>
#include <entities/CollidingRectangleEntity.h>


CollidingRectangleEntity::CollidingRectangleEntity() { m_Renderable = true; }

void CollidingRectangleEntity::AddRequired(h2d::FRect dims, bool showBoundingBox) {
    GameEntity::AddRequired();

    // TODO render rectangle with entity's heading
    auto c = std::make_shared<Collision2DComponent>(dims, showBoundingBox);
    AddComponent<Collision2DComponent>(c);
}

void CollidingRectangleEntity::AddInputHandler(
    std::function<void(float deltaTime, const std::vector<uint8_t> keys)>& onKeypress) {
    auto i = std::make_shared<InputComponent>();
    i->SetOnKeypress(onKeypress);
    AddComponent<InputComponent>(i);
}

void CollidingRectangleEntity::Update(float deltaTime) {
    auto transform = GetComponent<TransformComponent>(ComponentType::TransformComponent).value();

    transform->m_Transform.addTranslation(m_VelocityX * deltaTime, m_VelocityY * deltaTime);

    for (auto& [key, value] : m_Components) {
        m_Components[key]->Update(deltaTime);
    }
}

void CollidingRectangleEntity::Rotate(float rads) {
    auto transform = GetComponent<TransformComponent>(ComponentType::TransformComponent).value();
    m_Rotation += rads;
    h2d::Homogr rotated = h2d::Homogr().addRotation(rads);
    transform->m_Transform = transform->m_Transform * rotated;
}

float CollidingRectangleEntity::GetRotation() {
    return m_Rotation;
}

bool CollidingRectangleEntity::Intersects(const std::shared_ptr<CollidingRectangleEntity>& foo,
                                          const std::shared_ptr<CollidingRectangleEntity>& bar) {
    auto fooCollision = foo->GetComponent<Collision2DComponent>(ComponentType::Collision2DComponent).value();
    auto barCollision = bar->GetComponent<Collision2DComponent>(ComponentType::Collision2DComponent).value();
    return Collision2DComponent::Intersects(fooCollision, barCollision);
}

bool CollidingRectangleEntity::IntersectsFRect(const std::shared_ptr<CollidingRectangleEntity>& foo, h2d::FRect bar) {
    auto fooCollision = foo->GetComponent<Collision2DComponent>(ComponentType::Collision2DComponent).value();
    return Collision2DComponent::IntersectsFRect(fooCollision, bar);
}
