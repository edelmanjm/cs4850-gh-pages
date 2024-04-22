#pragma once

#include <SDL3/SDL.h>

#include <string>
#include <unordered_map>

/**
 * Manages resources, with automatic resource sharing and file I/O. Currently just for images, but easily extensible.
 */
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
    std::shared_ptr<SDL_Texture> LoadSvg(SDL_Renderer* renderer, const std::string& svg, float scale = 1.0);

    /**
     * Loads a supported image as a texture, using SDL_Image.
     * @param renderer The renderer to use for the image.
     * @param filepath The path to the image to load.
     * @return A shared pointer to the corresponding texture.
     */
    std::shared_ptr<SDL_Texture> LoadImage(SDL_Renderer* renderer, const std::string& filepath);

private:
    // Functor
    struct TextureFunctorDeleter {
        void operator()(SDL_Texture* texture) const { SDL_DestroyTexture(texture); }
    };

    static std::shared_ptr<SDL_Texture> MakeSharedTexture(SDL_Renderer* renderer, SDL_Surface* surface);

    /**
     * Copied from IMG_svg.c, but with the scale parameter actually exposed.
     * @param src
     * @param scale
     * @return
     */
    SDL_Surface* LoadScaledSvg(SDL_IOStream *src, float scale = 1.0);
};