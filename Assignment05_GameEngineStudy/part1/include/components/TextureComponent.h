#pragma once
#include <SDL3/SDL.h>
#include <memory>
#include <string>

#include <components/Component.h>

class TextureComponent : public Component {
public:
    TextureComponent();

    void CreateTextureComponent(SDL_Renderer* renderer, std::string filepath);

    ~TextureComponent() override;

    ComponentType GetType() override;

    void Input(float deltaTime) override;

    void Update(float deltaTime) override;

    void Render(SDL_Renderer* renderer) override;

private:
    std::shared_ptr<SDL_Texture> m_Texture;
};
