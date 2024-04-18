#pragma once
// Our 'key' when adding to a game object is based off
// of this enum.
//
// Declaration of our new type
enum class ComponentType {
    Collision2DComponent,
    InputComponent,
    LifetimeComponent,
    TransformComponent,
    TransformWrappingComponent,
    TextureComponent,
};
