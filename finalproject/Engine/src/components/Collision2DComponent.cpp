#include <components/Collision2DComponent.h>
#include <entities/GameEntity.h>

Collision2DComponent::Collision2DComponent(bool showBoundingBox) : m_ShowBoundingBox(showBoundingBox) {}

Collision2DComponent::~Collision2DComponent() {}

void Collision2DComponent::Input(float deltaTime) {}

void Collision2DComponent::Update(float deltaTime) {}

void Collision2DComponent::Render(SDL_Renderer* renderer) {
    if (m_ShowBoundingBox) {
        SDL_RenderFillRect(renderer, &getCollisionBox());
    }
}

bool Collision2DComponent::Intersects(std::shared_ptr<Collision2DComponent> foo, std::shared_ptr<Collision2DComponent> bar) {
    SDL_FRect result;
    return SDL_GetRectIntersectionFloat(&foo->getCollisionBox(), &bar->getCollisionBox(), &result);
}

SDL_FRect& Collision2DComponent::getCollisionBox() {
    // Default behavior for now is just to use the same box as the transformation; in the future, this could be updated
    // to allow for larger or smaller bounding boxes, as appropriate, and could also pull from fields of the
    // Collision2DComponent
    return GetGameEntity()->GetTransform()->m_Rectangle;
}

ComponentType Collision2DComponent::GetType() { return ComponentType::Collision2DComponent; }
