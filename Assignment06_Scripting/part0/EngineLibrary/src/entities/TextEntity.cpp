#include <SDL3_ttf/SDL_ttf.h>

#include <entities/TextEntity.h>

#include <utility>
#include "entities/CollidingRectangleEntity.h"

TextEntity::TextEntity(std::string fontPath, uint32_t fontSize, SDL_Color fontColor)
    : m_FontPath(std::move(fontPath))
    , m_FontSize(fontSize)
    , m_FontColor(fontColor) {
    m_Font = FC_CreateFont();
    SetRenderable(true);
}

TextEntity::~TextEntity() { FC_FreeFont(m_Font); }

void TextEntity::AddRequired(SDL_FRect transform) { GameEntity::AddRequired(transform); }

void TextEntity::Render(SDL_Renderer* renderer) {
    if (!m_FontLoaded) {
        FC_LoadFont(m_Font, renderer, m_FontPath.c_str(), m_FontSize, m_FontColor, TTF_STYLE_NORMAL);
        m_FontLoaded = true;
    }

    FC_Draw(m_Font, renderer, GetTransform()->m_Rectangle.x, GetTransform()->m_Rectangle.y, m_Text.c_str());
}