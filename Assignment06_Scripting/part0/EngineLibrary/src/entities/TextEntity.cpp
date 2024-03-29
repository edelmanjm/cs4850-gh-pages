#include <SDL3_ttf/SDL_ttf.h>

#include <entities/TextEntity.h>

TextEntity::TextEntity() {
    m_Font = FC_CreateFont();
    SetRenderable(true);
}

TextEntity::~TextEntity() { FC_FreeFont(m_Font); }

void TextEntity::Render(SDL_Renderer* renderer) {
    if (!m_FontLoaded) {
        FC_LoadFont(m_Font, renderer, "fonts/FreeSans.ttf", 20, FC_MakeColor(0, 0, 0, 255), TTF_STYLE_NORMAL);
        m_FontLoaded = true;
    }

    FC_Draw(m_Font, renderer, 0, 0, "This is %s.\n It works.", "example text");
}

void TextEntity::AddRequired(SDL_FRect transform) { GameEntity::AddRequired(transform); }