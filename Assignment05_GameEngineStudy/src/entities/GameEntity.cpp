#include <entities/GameEntity.h>

GameEntity::GameEntity(std::shared_ptr<Sprite> sprite) : m_Sprite(sprite) {
    m_Components.push_back(sprite);
}

void GameEntity::Input(float deltaTime) {

}

void GameEntity::Update(float deltaTime) {

}

void GameEntity::Render(SDL_Renderer *renderer) {
    for (std::shared_ptr<Component> c : m_Components) {
        c->Render(renderer);
    }
}

void GameEntity::SetRenderable(bool value) {
    m_Sprite->m_Renderable = value;
}

bool GameEntity::Intersects(const std::shared_ptr<GameEntity>& e) {
    SDL_FRect source = e->m_Sprite->GetRectangle();
    SDL_FRect us = m_Sprite->GetRectangle();
    SDL_FRect result;
    return SDL_GetRectIntersectionFloat(&source, &us, &result);
}

bool GameEntity::IsRenderable() const {
    return m_Sprite->m_Renderable;
}