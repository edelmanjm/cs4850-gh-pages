#pragma once

#include <SDL3/SDL.h>

#include <entities/GameEntity.h>

#include <cstdlib>
#include <memory>
#include <vector>

class Scene : public std::enable_shared_from_this<Scene> {
public:
    explicit Scene(SDL_Renderer* renderer);
    virtual ~Scene() = default;

    virtual void Input(float deltaTime) = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;

    virtual void AddEntity(const std::shared_ptr<GameEntity>& entity) = 0;
    virtual void RemoveEntity(std::shared_ptr<GameEntity> entity) = 0;

public:
    bool m_SceneIsActive{false};

protected:
    SDL_Renderer* m_Renderer;
};
