#pragma once

#include <vector>
#include <memory>

#include <SDL3/SDL.h>

#include <Scene.h>
#include <entities/EnemyEntity.h>
#include <entities/GameEntity.h>
#include <entities/PlayerGameEntity.h>
#include <entities/ProjectileEntity.h>

class Application {

private:
    std::unique_ptr<Scene> m_Scene;
    bool m_Run = true;
    SDL_Window* m_Window;
    const uint32_t m_Width = 640;
    const uint32_t m_Height = 480;
    SDL_Renderer *m_Renderer;

public:
    Application(int argc, char *argv[]);

    ~Application();

    void Input(float deltaTime);

    void Update(float deltaTime);

    void Render();

    void Loop(float targetFPS);
};
