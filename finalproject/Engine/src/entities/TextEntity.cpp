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

void TextEntity::AddRequired() { GameEntity::AddRequired(); }

void TextEntity::Render(SDL_Renderer* renderer) {
    if (!m_FontLoaded) {
        FC_LoadFont(m_Font, renderer, m_FontPath.c_str(), m_FontSize, m_FontColor, TTF_STYLE_NORMAL);
        m_FontLoaded = true;
    }

    h2d::Point2d origin(0, 0);
    h2d::Point2d transformed = GetTransform()->m_Transform * origin;
    FC_Draw(m_Font, renderer, static_cast<float>(transformed.getX()), static_cast<float>(transformed.getY()),
            m_Text.c_str());
}