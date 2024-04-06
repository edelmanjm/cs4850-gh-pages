#include <components/TextureComponent.h>
#include <components/TransformComponent.h>
#include <entities/GameEntity.h>
#include <utility/Geometry.h>

#include <utility>

TextureComponent::TextureComponent(std::shared_ptr<SDL_Texture> texture) : m_Texture(std::move(texture)) {};

TextureComponent::~TextureComponent() = default;

ComponentType TextureComponent::GetType() { return ComponentType::TextureComponent; }

void TextureComponent::Input(float deltaTime) {}
void TextureComponent::Update(float deltaTime) {}
void TextureComponent::Render(SDL_Renderer* renderer) {
    auto ge = GetGameEntity();
    auto transform = Geometry::AsSDL(ge->GetTransform()->m_Rectangle).value();
    if (nullptr == m_Texture) {
        SDL_RenderRect(renderer, &transform);
    } else {
        SDL_RenderTexture(renderer, m_Texture.get(), nullptr, &transform);
    }
}
