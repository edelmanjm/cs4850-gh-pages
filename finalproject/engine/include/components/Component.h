#pragma once
#include <SDL3/SDL.h>
#include <memory>

#include <components/ComponentType.h>

// Forward declaration of GameEntity, since GameEntity also relies on Component and we don't want a circular dependency
struct GameEntity;

/**
 * Components are the "building blocks" used to give entities functionality. Components are assigned as children to
 * their parent {@link GameEntity} and know of said association. Components must supply their {@link ComponentType}.
 */
class Component {
public:
    Component();

    virtual ~Component();

    virtual void Input(float deltaTime) = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render(SDL_Renderer* renderer) = 0;

    // Must be implemented
    virtual ComponentType GetType() = 0;

    void SetGameEntity(std::shared_ptr<GameEntity> g);

    std::shared_ptr<GameEntity> GetGameEntity();

    /// Some things to think about -- component communication
    /// void send(int message){}
    /// void receive(int message){}
private:
    std::shared_ptr<GameEntity> m_GameEntity;
};
