#include <ResourceManager.h>
#include <components/TextureComponent.h>
#include <components/TransformComponent.h>
#include <entities/GameEntity.h>
#include <utility/Geometry.h>

TextureComponent::TextureComponent() = default;

void TextureComponent::CreateTextureComponent(SDL_Renderer* renderer, std::string filepath) {
    m_Texture = ResourceManager::Instance().LoadTexture(renderer, std::move(filepath));
}

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
