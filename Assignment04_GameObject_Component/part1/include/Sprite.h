#pragma once

#include <SDL3/SDL.h>

#include <Component.h>

#include <memory>
#include <string>

class Sprite : public Component {
public:
    bool m_Renderable{true};

private:
    SDL_FRect m_Rectangle{20.0f, 20.0f, 32.0f, 32.0f};
    std::shared_ptr<SDL_Texture> m_Texture;

public:
    Sprite() = default;
    ~Sprite() = default;

    void CreateSprite(SDL_Renderer* renderer, std::string filepath);

    void Input(float deltaTime) override;

    void Update(float deltaTime) override;

    void Render(SDL_Renderer* renderer) override;

    void SetW(float w);

    void SetX(float x);

    void SetY(float y);

    [[nodiscard]] float GetX() const;

    [[nodiscard]] float GetY() const;

    void Move(float x, float y);

    [[nodiscard]] SDL_FRect GetRectangle() const;
};