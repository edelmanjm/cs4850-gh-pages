#pragma once

#include <vector>
#include <memory>

#include <SDL3/SDL.h>

#include <entities/EnemyEntity.h>
#include <entities/GameEntity.h>
#include <entities/PlayerGameEntity.h>
#include <entities/ProjectileEntity.h>
#include <Sprite.h>

class Application {

private:
    // Enemy sprites
    std::vector<std::unique_ptr<EnemyEntity>> m_Enemies;
    // Main Character
    std::unique_ptr<PlayerGameEntity> m_MainCharacter;

    bool m_Run{true};
    float m_Points{0.0f};
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
