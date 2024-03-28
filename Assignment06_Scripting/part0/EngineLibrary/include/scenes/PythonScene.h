#pragma once

#include <Renderer.h>
#include <scenes/Scene.h>

class PythonScene : public Scene {
public:
    PythonScene(std::shared_ptr<Renderer> renderer);

    void Input(float deltaTime) override;
    void Update(float deltaTime) override;
    void Render() override;

private:
};