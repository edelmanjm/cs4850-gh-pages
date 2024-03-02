#include <ResourceManager.h>
#include <components/TextureComponent.h>
#include <components/TransformComponent.h>
#include <entities/GameEntity.h>

TextureComponent::TextureComponent() {}

void TextureComponent::CreateTextureComponent(SDL_Renderer* renderer, std::string filepath) {
    m_Texture = ResourceManager::Instance().LoadTexture(renderer, filepath);
}

TextureComponent::~TextureComponent() {}

ComponentType TextureComponent::GetType() { return ComponentType::TextureComponent; }

void TextureComponent::Input(float deltaTime) {}
void TextureComponent::Update(float deltaTime) {}
void TextureComponent::Render(SDL_Renderer* renderer) {
    if (nullptr == m_Texture) {
        auto ge = GetGameEntity();
        auto transform = ge->GetTransform()->GetRectangle();
        SDL_RenderRect(renderer, &transform);
    } else {
        auto ge = GetGameEntity();
        auto transform = ge->GetTransform()->GetRectangle();

        SDL_RenderTexture(renderer, m_Texture.get(), nullptr, &transform);
    }
}
