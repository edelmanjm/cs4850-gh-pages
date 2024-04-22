#pragma once
#include <memory>
#include <string>

#include <homog2d.hpp>

#include <components/Component.h>

/**
 * A transform component stores a transform, backed by a {@link h2d::Homogr}. All entities include this component by
 * default.
 */
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
