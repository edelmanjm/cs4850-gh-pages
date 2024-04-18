#include <components/LifetimeComponent.h>
#include <entities/GameEntity.h>
#include <scenes/Scene.h>

LifetimeComponent::LifetimeComponent(uint32_t interval) {
    m_TimerId = SDL_AddTimer(interval, &Dispatch, this);
}

ComponentType LifetimeComponent::GetType() { return ComponentType::LifetimeComponent; }

void LifetimeComponent::Input(float deltaTime) {}

void LifetimeComponent::Update(float deltaTime) {}

void LifetimeComponent::Render(SDL_Renderer* renderer) {}

uint32_t LifetimeComponent::Dispatch(uint32_t interval, void *param) {
    static_cast<LifetimeComponent*>(param)->Despawn(interval);
    return 0;
}

void LifetimeComponent::Despawn(uint32_t interval) {
    auto ge = GetGameEntity();
    ge->m_ParentScene->RemoveEntity(ge);
}