#include <components/TextureComponent.h>
#include <components/TransformComponent.h>
#include <entities/GameEntity.h>
#include <utility/Geometry.h>

#include <utility>

TextureComponent::TextureComponent(std::shared_ptr<SDL_Texture> texture, h2d::FRect box)
    : m_Texture(std::move(texture))
    , m_Box(box){};

TextureComponent::~TextureComponent() = default;

ComponentType TextureComponent::GetType() { return ComponentType::TextureComponent; }

void TextureComponent::Input(float deltaTime) {}
void TextureComponent::Update(float deltaTime) {}
void TextureComponent::Render(SDL_Renderer* renderer) {
    auto ge = GetGameEntity();
    auto translated = (ge->GetTransform()->m_Transform * m_Box.getPts().first);
    SDL_FRect bounded{static_cast<float>(translated.getX()), static_cast<float>(translated.getY()),
                      static_cast<float>(m_Box.width()), static_cast<float>(m_Box.height())};
    if (nullptr == m_Texture) {
        SDL_RenderRect(renderer, &bounded);
    } else {
        SDL_RenderTexture(renderer, m_Texture.get(), nullptr, &bounded);
    }
}
