#pragma once

#include <SDL_FontCache.h>

#include <entities/GameEntity.h>

class TextEntity : public GameEntity {
public:
    TextEntity();
    ~TextEntity();
    void AddRequired(SDL_FRect transform) override;

    void Render(SDL_Renderer *renderer) override;

private:
    FC_Font* m_Font;
    bool m_FontLoaded = false;
};