#include <scenes/PythonScene.h>

PythonScene::PythonScene(std::shared_ptr<Renderer> renderer) : Scene(renderer->m_Wrapped) {}

void PythonScene::Input(float deltaTime) {
    // TODO
}

void PythonScene::Update(float deltaTime) {
    // TODO
}

void PythonScene::Render() {
    SDL_SetRenderDrawColor(m_Renderer, 32, 32, 64, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(m_Renderer);

    SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    SDL_RenderPresent(m_Renderer);
}