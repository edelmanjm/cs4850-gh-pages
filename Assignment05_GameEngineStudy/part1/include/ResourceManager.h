#pragma once

#include <SDL3/SDL.h>

#include <string>
#include <unordered_map>

class ResourceManager {
private:
    std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> m_TextureResources;

private:
    ResourceManager() = default;

public:
    static ResourceManager& Instance();
    ResourceManager(ResourceManager const&) = delete;
    void operator=(ResourceManager const&) = delete;

    std::shared_ptr<SDL_Texture> LoadTexture(SDL_Renderer* renderer, std::string filepath);

private:
    // Functor
    struct TextureFunctorDeleter {
        void operator()(SDL_Texture* texture) const { SDL_DestroyTexture(texture); }
    };

    static std::shared_ptr<SDL_Texture> MakeSharedTexture(SDL_Renderer* renderer, SDL_Surface* pixels);
};