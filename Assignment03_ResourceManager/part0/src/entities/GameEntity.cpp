#include <entities/GameEntity.h>

GameEntity::GameEntity(Sprite sprite) {
    m_Sprite = sprite;
}

void GameEntity::Input(float deltaTime) {

}

void GameEntity::Update(float deltaTime) {

}

void GameEntity::Render(SDL_Renderer *renderer) {

}

void GameEntity::SetRenderable(bool value) {
    m_Renderable = value;
}

bool GameEntity::Intersects(const std::shared_ptr<GameEntity>& e) {
    SDL_FRect source = e->m_Sprite.GetRectangle();
    SDL_FRect us = m_Sprite.GetRectangle();
    SDL_FRect result;
    return SDL_GetRectIntersectionFloat(&source, &us, &result);
}

bool GameEntity::IsRenderable() const {
    return m_Renderable;
}