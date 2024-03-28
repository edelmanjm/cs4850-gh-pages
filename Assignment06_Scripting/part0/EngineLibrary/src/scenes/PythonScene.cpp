#include <scenes/PythonScene.h>

#include <utility>

PythonScene::PythonScene(std::shared_ptr<Renderer> renderer) : Scene(renderer->m_Wrapped) {}

void PythonScene::Input(float deltaTime) {
    // TODO Call a Python function to handle the input
}

void PythonScene::Update(float deltaTime) {
    for (const auto& e : m_Entities) {
        e->Update(deltaTime);
    }

    // Typically calls Python code
    m_OnUpdate(deltaTime);
}

void PythonScene::Render() {
    SDL_SetRenderDrawColor(m_Renderer, 32, 32, 64, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(m_Renderer);

    SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    for (const auto& e : m_Entities) {
        e->Render(m_Renderer);
    }

    SDL_RenderPresent(m_Renderer);
}

void PythonScene::SetOnUpdate(std::function<void(float deltaTime)> onUpdate) {
    m_OnUpdate = std::move(onUpdate);
}

void PythonScene::AddEntity(const std::shared_ptr<CollidingRectangleEntity>& entity) {
    m_Entities.push_back(entity);
}