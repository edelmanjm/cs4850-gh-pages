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

    std::shared_ptr<SDL_Texture> LoadTexture(SDL_Renderer* renderer, const std::string& filepath);

    /**
     * Loads an SVG as a texture.
     * @param renderer The renderer to use for the SVG.
     * @param svg An SVG, as a string. Note that this is *not* a path to an SVG file, but rather the SVG itself.
     * @return A shared pointer to the responding texture.
     */
    std::shared_ptr<SDL_Texture> LoadSvg(SDL_Renderer* renderer, const std::string& svg);

private:
    // Functor
    struct TextureFunctorDeleter {
        void operator()(SDL_Texture* texture) const { SDL_DestroyTexture(texture); }
    };

    static std::shared_ptr<SDL_Texture> MakeSharedTexture(SDL_Renderer* renderer, SDL_Surface* surface);
};