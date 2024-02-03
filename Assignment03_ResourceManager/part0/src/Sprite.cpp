#include <ResourceManager.h>
#include <Sprite.h>

void Sprite::CreateSprite(SDL_Renderer* renderer, std::string filepath) {
    m_Texture = ResourceManager::Instance().LoadTexture(renderer, filepath);
}

void Sprite::Update(float deltaTime) {
    // TODO
}

void Sprite::Render(SDL_Renderer* renderer) {
    if (nullptr == m_Texture) {
        SDL_RenderRect(renderer, &m_Rectangle);
    } else {
        SDL_RenderTexture(renderer, m_Texture.get(), nullptr, &m_Rectangle);
    }
}

void Sprite::SetW(float w) { m_Rectangle.w = w; }

void Sprite::SetX(float x) { m_Rectangle.x = x; }

void Sprite::SetY(float y) { m_Rectangle.y = y; }

[[nodiscard]] float Sprite::GetX() const { return m_Rectangle.x; }

[[nodiscard]] float Sprite::GetY() const { return m_Rectangle.y; }

void Sprite::Move(float x, float y) {
    m_Rectangle.x = x;
    m_Rectangle.y = y;
}

[[nodiscard]] SDL_FRect Sprite::GetRectangle() const { return m_Rectangle; }