#pragma once

#include <components/Component.h>

/**
 * A lifetime component automatically hides (or, optionally, despawns) its parent entity when its lifetime expires.
 * An internal SDL timer keeps track of this lifetime.
 *
 * Be careful with these, otherwise you may get segfaults!
 */
class LifetimeComponent : public Component {
public:
    explicit LifetimeComponent(uint32_t interval);

    ComponentType GetType() override;

    void Input(float deltaTime) override;

    void Update(float deltaTime) override;

    void Render(SDL_Renderer* renderer) override;

private:
    // Must be static because SDL; takes the instance as userdata.
    // See https://stackoverflow.com/questions/19938531/
    static uint32_t Dispatch(uint32_t interval, void *param);
    void Despawn(uint32_t interval);

private:
    SDL_TimerID m_TimerId;
};