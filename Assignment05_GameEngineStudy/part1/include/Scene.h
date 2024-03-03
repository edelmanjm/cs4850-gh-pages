#pragma once

#include <SDL3/SDL.h>

#include <cstdlib>
#include <memory>
#include <vector>

#include <entities/EnemyEntity.h>
#include <entities/PlayerGameEntity.h>

class Scene {
public:
    Scene(SDL_Renderer* renderer, uint32_t width);
    ~Scene();

    void Input(float deltaTime);
    void Update(float deltaTime);
    void Render();
    void SetSceneActiveStatus(bool status);
    bool IsSceneActive() const;

private:
    std::vector<std::shared_ptr<EnemyEntity>> m_Enemies;
    std::shared_ptr<PlayerGameEntity> m_MainCharacter;
    float m_Points{0.0f};

    bool m_SceneIsActive{false};
    SDL_Renderer* m_Renderer;
};
