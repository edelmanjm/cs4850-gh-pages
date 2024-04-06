#pragma once
#include <memory>
#include <string>

#include <SDL3/SDL.h>
#include <homog2d.hpp>

#include <components/Component.h>

class Collision2DComponent : public Component {
public:
    Collision2DComponent(bool showBoundingBox = false);

    ~Collision2DComponent() override;

    ComponentType GetType() override;

    void Input(float deltaTime) override;

    void Update(float deltaTime) override;

    void Render(SDL_Renderer* renderer) override;

    static bool Intersects(std::shared_ptr<Collision2DComponent> foo, std::shared_ptr<Collision2DComponent> bar);

private:
    h2d::FRect getCollisionBox();

private:
//    SDL_FRect m_Rectangle;
    bool m_ShowBoundingBox;
};
