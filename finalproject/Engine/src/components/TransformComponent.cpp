#include <components/TransformComponent.h>

TransformComponent::TransformComponent(h2d::FRect rectangle) : m_Rectangle(rectangle) {}

TransformComponent::TransformComponent(SDL_FRect rectangle) {
    m_Rectangle.set(rectangle.x, rectangle.y, rectangle.x + rectangle.w, rectangle.y + rectangle.h);
}

TransformComponent::~TransformComponent() = default;

void TransformComponent::Input(float deltaTime) {}

void TransformComponent::Update(float deltaTime) {}

void TransformComponent::Render(SDL_Renderer* renderer) {}

ComponentType TransformComponent::GetType() { return ComponentType::TransformComponent; }

std::optional<SDL_FRect> TransformComponent::AsSDL() {
    auto points = m_Rectangle.get4Pts();
    if (points[0].getX() == points[1].getX()) {
        return SDL_FRect{static_cast<float>(points[0].getX()), static_cast<float>(points[0].getY()),
                         static_cast<float>(m_Rectangle.height()), static_cast<float>(m_Rectangle.width())};
    } else {
        return std::nullopt;
    }
}

double TransformComponent::GetX() const {
    return m_Rectangle.getPts().first.getX();
}

double TransformComponent::GetY() const {
    return m_Rectangle.getPts().first.getY();
}

void TransformComponent::SetX(double x) {
    auto smallest = m_Rectangle.getPts().first;
    m_Rectangle.moveTo(x, smallest.getY());
}

void TransformComponent::SetY(double y) {
    auto smallest = m_Rectangle.getPts().first;
    m_Rectangle.moveTo(smallest.getX(), y);
}