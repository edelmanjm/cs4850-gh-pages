#pragma once

#include <memory>

#include <Component.h>
#include <Sprite.h>

class GameEntity : Component {

protected:
    // I refuse to use dynamic casting as the lookup query for the sprite in the components lol.
    // We can revisit having this as a separate field after the next assignment.
    const std::shared_ptr<Sprite> m_Sprite;
    std::vector<std::shared_ptr<Component>> m_Components;

public:
    explicit GameEntity(std::shared_ptr<Sprite> sprite);

    virtual ~GameEntity() = default;

    void Input(float deltaTime) override;

    void Update(float deltaTime) override;

    void Render(SDL_Renderer *renderer) override;

    void SetRenderable(bool value);

    [[nodiscard]] bool IsRenderable() const;

    bool Intersects(const std::shared_ptr<GameEntity>& e);
};