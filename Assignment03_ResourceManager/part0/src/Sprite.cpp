#include <Sprite.h>

void Sprite::CreateSprite(SDL_Renderer *renderer, const char *filepath)  {
    SDL_Surface *pixels = SDL_LoadBMP(filepath);
    SDL_SetSurfaceColorKey(pixels, SDL_TRUE, SDL_MapRGB(pixels->format, 0xFF, 0, 0xFF));

    m_Texture = SDL_CreateTextureFromSurface(renderer, pixels);
    if (nullptr == m_Texture) {
        SDL_Log("Could not load texture from surface");
    }

    SDL_DestroySurface(pixels);
}

void Sprite::Update(float deltaTime) {
    // TODO
}

void Sprite::Render(SDL_Renderer *renderer)  {
    if (nullptr == m_Texture) {
        SDL_RenderRect(renderer, &m_Rectangle);
    } else {
        SDL_RenderTexture(renderer, m_Texture, nullptr, &m_Rectangle);
    }
}

void Sprite::SetW(float w) {
    m_Rectangle.w = w;
}

void Sprite::SetX(float x) {
    m_Rectangle.x = x;
}

void Sprite::SetY(float y) {
    m_Rectangle.y = y;
}

[[nodiscard]] float Sprite::GetX() const  {
    return m_Rectangle.x;
}

[[nodiscard]] float Sprite::GetY() const {
    return m_Rectangle.y;
}

void Sprite::Move(float x, float y) {
    m_Rectangle.x = x;
    m_Rectangle.y = y;
}

[[nodiscard]] SDL_FRect Sprite::GetRectangle() const {
    return m_Rectangle;
}