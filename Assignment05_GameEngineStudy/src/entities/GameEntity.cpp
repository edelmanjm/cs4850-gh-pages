#include <components/Collision2DComponent.h>
#include <entities/GameEntity.h>

GameEntity::GameEntity() {
    // TODO this errors, but...
//    std::shared_ptr<TransformComponent> t = std::make_shared<TransformComponent>();
//    AddComponent<TransformComponent>(t);
};

GameEntity::~GameEntity() = default;

void GameEntity::Input(float deltaTime) {
    for (auto& [key, value] : m_Components) {
        m_Components[key]->Input(deltaTime);
    }
}

void GameEntity::Update(float deltaTime) {
    for (auto& [key, value] : m_Components) {
        m_Components[key]->Update(deltaTime);
    }
}

void GameEntity::Render(SDL_Renderer* renderer) {
    for (auto& [key, value] : m_Components) {
        m_Components[key]->Render(renderer);
    }
}

bool GameEntity::Intersects(const std::shared_ptr<GameEntity>& e) {
    auto source = e->GetComponent<Collision2DComponent>(ComponentType::Collision2DComponent).value()->GetRectangle();
    auto us = GetComponent<Collision2DComponent>(ComponentType::Collision2DComponent).value()->GetRectangle();
    /*
    SDL_FRect source = e->mSprite.GetRectangle();
    SDL_FRect us     = mSprite.GetRectangle();
    */
    SDL_FRect result;
    return SDL_GetRectIntersectionFloat(&source, &us, &result);
}

std::shared_ptr<TransformComponent> GameEntity::GetTransform(){
    // TODO ...this seems to have other issues?
    auto maybe = GetComponent<TransformComponent>(ComponentType::TransformComponent);
    if (maybe) {
        return maybe.value();
    } else {
        std::shared_ptr<TransformComponent> t = std::make_shared<TransformComponent>();
        AddComponent<TransformComponent>(t);
        return t;
    }
}

bool GameEntity::IsRenderable() const { return m_Renderable; }
void GameEntity::SetRenderable(bool mRenderable) { m_Renderable = mRenderable; }
