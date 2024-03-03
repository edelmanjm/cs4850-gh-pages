#include <components/Collision2DComponent.h>
#include <entities/GameEntity.h>

Collision2DComponent::Collision2DComponent() {}

Collision2DComponent::~Collision2DComponent() {}

void Collision2DComponent::Input(float deltaTime) {}

void Collision2DComponent::Update(float deltaTime) {
    /// NOTE: Default behavior will be to just update the
    //        Collision2DComponent with the objects transform.
    //        Later, we may want to have more control here.
    auto transform = GetGameEntity()->GetTransform();
    SetWH(transform->GetW(), transform->GetH());
    SetXY(transform->GetX(), transform->GetY());
}

void Collision2DComponent::Render(SDL_Renderer* renderer) {
    // Useful for debugging purposes
    SDL_RenderRect(renderer, &m_Rectangle);
}

ComponentType Collision2DComponent::GetType() { return ComponentType::Collision2DComponent; }

void Collision2DComponent::SetW(float w) { m_Rectangle.w = w; }

void Collision2DComponent::SetH(float h) { m_Rectangle.h = h; }

void Collision2DComponent::SetWH(float w, float h) {
    m_Rectangle.w = w;
    m_Rectangle.h = h;
}

float Collision2DComponent::GetW() const { return m_Rectangle.w; }

float Collision2DComponent::GetH() const { return m_Rectangle.h; }

void Collision2DComponent::SetX(float x) { m_Rectangle.x = x; }

void Collision2DComponent::SetY(float y) { m_Rectangle.y = y; }

void Collision2DComponent::SetXY(float x, float y) {
    m_Rectangle.x = x;
    m_Rectangle.y = y;
}

float Collision2DComponent::GetX() const { return m_Rectangle.x; }

float Collision2DComponent::GetY() const { return m_Rectangle.y; }

SDL_FRect Collision2DComponent::GetRectangle() const { return m_Rectangle; }
