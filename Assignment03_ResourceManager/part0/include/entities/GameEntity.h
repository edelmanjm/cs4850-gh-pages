#pragma once

#include <memory>
#include <Sprite.h>

class GameEntity {

protected:
    Sprite m_Sprite;
    bool m_Renderable{true};

public:
    explicit GameEntity(Sprite sprite);

    virtual ~GameEntity() = default;

    virtual void Input(float deltaTime);

    virtual void Update(float deltaTime);

    virtual void Render(SDL_Renderer *renderer);

    void SetRenderable(bool value);

    [[nodiscard]] bool IsRenderable() const;

    bool Intersects(const std::shared_ptr<GameEntity>& e);
};