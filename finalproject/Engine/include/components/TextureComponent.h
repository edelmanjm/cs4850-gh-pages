#pragma once
#include <memory>
#include <string>

#include <SDL3/SDL.h>
#include <homog2d.hpp>

#include <components/Component.h>

class TextureComponent : public Component {
public:
    TextureComponent(std::shared_ptr<SDL_Texture> texture, h2d::FRect box);

    ~TextureComponent() override;

    ComponentType GetType() override;

    void Input(float deltaTime) override;

    void Update(float deltaTime) override;

    void Render(SDL_Renderer* renderer) override;

private:
    h2d::FRect m_Box;
    std::shared_ptr<SDL_Texture> m_Texture;
};
