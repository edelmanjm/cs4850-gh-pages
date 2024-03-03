#include <components/Collision2DComponent.h>
#include <entities/GameEntity.h>

GameEntity::GameEntity() = default;

GameEntity::~GameEntity() = default;

void GameEntity::AddRequired() {
    std::shared_ptr<TransformComponent> t = std::make_shared<TransformComponent>();
    AddComponent<TransformComponent>(t);
}

void GameEntity::Input(float deltaTime) {
    for (auto& [key, value] : m_Components) {
        m_Components[key]->Input(deltaTime);
    }

    for (auto& child : m_Children) {
        child->Input(deltaTime);
    }
}

void GameEntity::Update(float deltaTime) {
    for (auto& [key, value] : m_Components) {
        m_Components[key]->Update(deltaTime);
    }

    for (auto& child : m_Children) {
        child->Update(deltaTime);
    }
}

void GameEntity::Render(SDL_Renderer* renderer) {
    if (IsRenderable()) {
        for (auto& [key, value] : m_Components) {
            m_Components[key]->Render(renderer);
        }
    }

    for (auto& child : m_Children) {
        child->Render(renderer);
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

void GameEntity::AddChild(std::shared_ptr<GameEntity> child) {
    m_Children.push_back(child);
}

std::shared_ptr<GameEntity> GameEntity::GetChildAtIndex(size_t i) {
    return m_Children.at(i);
}

std::shared_ptr<TransformComponent> GameEntity::GetTransform(){
    return GetComponent<TransformComponent>(ComponentType::TransformComponent).value();
}

bool GameEntity::IsRenderable() const { return m_Renderable; }
void GameEntity::SetRenderable(bool mRenderable) { m_Renderable = mRenderable; }
