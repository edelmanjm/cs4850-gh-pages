#pragma once

/**
 * Used to distinguish components from each other when adding/retriving them from an entityt.
 */
enum class ComponentType {
    Collision2DComponent,
    InputComponent,
    LifetimeComponent,
    TransformComponent,
    TransformWrappingComponent,
    TextureComponent,
};
