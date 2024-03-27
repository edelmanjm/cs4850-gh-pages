#pragma once

#include <scenes/Scene.h>

class PythonScene : public Scene {
public:
    PythonScene(SDL_Renderer* renderer);
    ~PythonScene() override;

    void Input(float deltaTime) override;
    void Update(float deltaTime) override;
    void Render() override;

private:
};