#pragma once

#include <SDL3/SDL.h>

#include <cstdlib>
#include <memory>
#include <vector>

#include <entities/EnemyEntity.h>
#include <entities/PlayerGameEntity.h>

class Scene {
public:
    explicit Scene(SDL_Renderer* renderer);
    virtual ~Scene();

    virtual void Input(float deltaTime) = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;

public:
    bool m_SceneIsActive{false};

protected:
    SDL_Renderer* m_Renderer;
};
