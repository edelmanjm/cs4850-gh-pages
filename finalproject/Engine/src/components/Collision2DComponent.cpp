#include <components/Collision2DComponent.h>
#include <entities/GameEntity.h>
#include <utility/Geometry.h>

Collision2DComponent::Collision2DComponent(bool showBoundingBox) : m_ShowBoundingBox(showBoundingBox) {}

Collision2DComponent::~Collision2DComponent() {}

void Collision2DComponent::Input(float deltaTime) {}

void Collision2DComponent::Update(float deltaTime) {}

void Collision2DComponent::Render(SDL_Renderer* renderer) {
    if (m_ShowBoundingBox) {
        std::array<SDL_Vertex, 4> vertices{};
        std::array<h2d::Point2d, 4> points = getCollisionBox().get4Pts();
        std::transform(points.begin(), points.end(), vertices.begin(), [](h2d::Point2d& pt) {
            return SDL_Vertex{static_cast<float>(pt.getX()), static_cast<float>(pt.getY()), 255, 255, 255, 255};
        });
        auto indices = std::array{0, 1, 2, 0, 2, 3};
        SDL_RenderGeometry(renderer, nullptr, vertices.data(), vertices.size(), indices.data(), indices.size());
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
