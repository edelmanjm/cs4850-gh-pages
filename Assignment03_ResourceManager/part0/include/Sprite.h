#pragma once

#include <SDL3/SDL.h>

class Sprite {

private:
    SDL_FRect m_Rectangle{20.0f, 20.0f, 32.0f, 32.0f};
    SDL_Texture* m_Texture;

public:
    Sprite() = default;
    ~Sprite() = default;
//        TODO: We'll want a resource manager to handle this.
//        SDL_DestroyTexture(m_Texture);

    void CreateSprite(SDL_Renderer *renderer, const char *filepath);

    void Update(float deltaTime);

    void Render(SDL_Renderer *renderer);

    void SetW(float w);

    void SetX(float x);

    void SetY(float y);

    [[nodiscard]] float GetX() const;

    [[nodiscard]] float GetY() const;

    void Move(float x, float y);

    [[nodiscard]] SDL_FRect GetRectangle() const;
};