#pragma once

#include <memory>
#include <map>

#include <components/Component.h>
#include <components/TransformComponent.h>

class GameEntity : public std::enable_shared_from_this<GameEntity> {

private:
    bool m_Renderable = true;

protected:
    std::map<ComponentType, std::shared_ptr<Component>> m_Components;

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
    bool IsRenderable() const;
    void SetRenderable(bool mRenderable);

    bool Intersects(const std::shared_ptr<GameEntity>& e);
};