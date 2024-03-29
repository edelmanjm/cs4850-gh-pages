#pragma once

#include <SDL_FontCache.h>

#include <entities/GameEntity.h>

class TextEntity : public GameEntity {
public:
    TextEntity(std::string fontPath, uint32_t fontSize, SDL_Color fontColor);
    ~TextEntity();
    void AddRequired(SDL_FRect transform) override;

    void Render(SDL_Renderer *renderer) override;

public:
    std::string m_Text;

private:
    std::string m_FontPath;
    uint32_t m_FontSize;
    SDL_Color m_FontColor;
    FC_Font* m_Font;
    bool m_FontLoaded = false;
};