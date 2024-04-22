#pragma once

#include <memory>
#include <map>

#include <components/Component.h>
#include <components/TransformComponent.h>

// Forward declaration
class Scene;

/**
 * GameEntities are the main "things" in a scene. They represent individual contents of the scene, and have child
 * components to provide functionality. GameEntities may also have child entities. GameEntities know which scene they
 * are placed in.
 */
class GameEntity : public std::enable_shared_from_this<GameEntity> {

public:
    GameEntity();
    virtual ~GameEntity();

    virtual void Input(float deltaTime);
    virtual void Update(float deltaTime);
    virtual void Render(SDL_Renderer *renderer);

    // Not feeling like creating a .tpp file right now, and I don't like explicit template instantiations

    template <typename T>
    void AddComponent(std::shared_ptr<T> c) {
        // NOTE: You could use the template information to get
        //       the exact component type
        m_Components[c->GetType()] = c;
        c->SetGameEntity(shared_from_this());
    }

    void AddChild(std::shared_ptr<GameEntity>);
    std::shared_ptr<GameEntity> GetChildAtIndex(size_t i);

    template <typename T>
    std::optional<std::shared_ptr<T>> GetComponent(ComponentType type) {
        auto found = m_Components.find(type);
        if (found != m_Components.end()) {
            return dynamic_pointer_cast<T>(found->second);
        } else {
            return {};
        }
    }

    std::shared_ptr<TransformComponent> GetTransform();
    h2d::Point2d GetTransformedOrigin();

    bool Intersects(const std::shared_ptr<GameEntity>& e);

protected:
    /**
     * Adds the required components and child entities for this entity to itself. This is basically an initialization
     * function; the reason this isn't in the constructor is because AddComponent() relies on shared_from_this(),
     * which requires that the object already be initialized. Derived classes should implement a public-facing
     * version of this method which takes the required arguments.
     */
    virtual void AddRequired();

public:
    std::shared_ptr<Scene> m_ParentScene;
    bool m_Renderable = true;

protected:
    std::map<ComponentType, std::shared_ptr<Component>> m_Components;
    std::vector<std::shared_ptr<GameEntity>> m_Children;
};