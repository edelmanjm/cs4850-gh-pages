#pragma once

#include <vector>
#include <memory>

#include <SDL3/SDL.h>

#include <Renderer.h>
#include <scenes/Scene.h>
#include <entities/GameEntity.h>
#include <entities/invaders/EnemyEntity.h>
#include <entities/invaders/PlayerGameEntity.h>
#include <entities/ProjectileEntity.h>

class Application {

private:
    std::optional<std::shared_ptr<Scene>> m_Scene;

private:
    std::shared_ptr<Renderer> m_Renderer;

public:
    Application(std::shared_ptr<Renderer> renderer);
    ~Application();

    void setScene(const std::shared_ptr<Scene>& scene);

    void Input(float deltaTime);
    void Update(float deltaTime);
    void Render();

    void Loop(float targetFPS);
};
