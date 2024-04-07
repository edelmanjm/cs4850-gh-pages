#pragma once
#include <memory>
#include <string>

#include <homog2d.hpp>

#include <components/Component.h>

class TransformComponent : public Component {
public:
    TransformComponent();

    ~TransformComponent() override;

    ComponentType GetType() override;

    void Input(float deltaTime) override;

    void Update(float deltaTime) override;

    void Render(SDL_Renderer* renderer) override;

public:
    h2d::Homogr m_Transform;
};
