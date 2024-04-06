#include <components/Collision2DComponent.h>
#include <entities/GameEntity.h>
#include <utility/Geometry.h>

Collision2DComponent::Collision2DComponent(bool showBoundingBox) : m_ShowBoundingBox(showBoundingBox) {}

Collision2DComponent::~Collision2DComponent() {}

void Collision2DComponent::Input(float deltaTime) {}

void Collision2DComponent::Update(float deltaTime) {}

void Collision2DComponent::Render(SDL_Renderer* renderer) {
    if (m_ShowBoundingBox) {
        auto collisionBox = getCollisionBox();
        auto converted = Geometry::AsSDL(collisionBox);
        if (converted) {
            SDL_RenderFillRect(renderer, &converted.value());
        }
    }
}

bool Collision2DComponent::Intersects(std::shared_ptr<Collision2DComponent> foo, std::shared_ptr<Collision2DComponent> bar) {
    h2d::FRect fooBox = foo->getCollisionBox();
    h2d::FRect barBox = bar->getCollisionBox();
    return fooBox.intersects(barBox)();
}

h2d::FRect Collision2DComponent::getCollisionBox() {
    // Default behavior for now is just to use the same box as the transformation; in the future, this could be updated
    // to allow for larger or smaller bounding boxes, as appropriate, and could also pull from fields of the
    // Collision2DComponent
    return GetGameEntity()->GetTransform()->m_Rectangle;
}

ComponentType Collision2DComponent::GetType() { return ComponentType::Collision2DComponent; }
