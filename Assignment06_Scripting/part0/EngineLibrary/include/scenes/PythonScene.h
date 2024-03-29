#pragma once

#include <Renderer.h>
#include <entities/CollidingRectangleEntity.h>
#include <scenes/Scene.h>

class PythonScene : public Scene {
public:
    PythonScene(std::shared_ptr<Renderer> renderer);

    void Input(float deltaTime) override;
    void Update(float deltaTime) override;
    void Render() override;
    void SetOnUpdate(std::function<void(float deltaTime)> onUpdate);

    void AddEntity(const std::shared_ptr<GameEntity>& entity);

private:
    std::vector<std::shared_ptr<GameEntity>> m_Entities;
    /**
     * This function is called on every Update(). The intended use is that per-tick game logic will be written in
     * Python, with C++ calling the Python code each tick.
     */
    std::function<void(float deltaTime)> m_OnUpdate;
};