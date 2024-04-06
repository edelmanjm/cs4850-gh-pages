#pragma once

#include <entities/invaders/EnemyEntity.h>
#include <entities/invaders/PlayerGameEntity.h>
#include <scenes/Scene.h>

class SpaceInvaders : public Scene {
public:
    SpaceInvaders(SDL_Renderer* renderer, uint32_t width);
    ~SpaceInvaders() override;

    void Input(float deltaTime) override;
    void Update(float deltaTime) override;
    void Render() override;

private:
    std::vector<std::shared_ptr<EnemyEntity>> m_Enemies;
    std::shared_ptr<PlayerGameEntity> m_MainCharacter;
    float m_Points{0.0f};
};