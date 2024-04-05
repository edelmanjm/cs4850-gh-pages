#include <SDL3_ttf/SDL_ttf.h>

#include <entities/CollidingRectangleEntity.h>
#include <entities/TextEntity.h>
#include <utility/Geometry.h>

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

    FC_Draw(m_Font, renderer, static_cast<float>(Geometry::GetX(GetTransform()->m_Rectangle)),
            static_cast<float>(Geometry::GetY(GetTransform()->m_Rectangle)), m_Text.c_str());
}