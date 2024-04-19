#include <SDL3_image/SDL_image.h>

#include <ResourceManager.h>

ResourceManager& ResourceManager::Instance() {
    static ResourceManager instance;
    return instance;
}

std::shared_ptr<SDL_Texture> ResourceManager::LoadTexture(SDL_Renderer* renderer, const std::string& filepath)  {
    if (!m_TextureResources.contains(filepath)) {
        SDL_Surface* pixels = SDL_LoadBMP(filepath.c_str());
        SDL_SetSurfaceColorKey(pixels, SDL_TRUE, SDL_MapRGB(pixels->format, 0xFF, 0, 0xFF));
        std::shared_ptr<SDL_Texture> texture = MakeSharedTexture(renderer, pixels);
        m_TextureResources.insert({filepath, texture});

        SDL_DestroySurface(pixels);
    }

    return m_TextureResources[filepath];
}

std::shared_ptr<SDL_Texture> ResourceManager::LoadSvg(SDL_Renderer* renderer, const std::string& svg) {
    if (!m_TextureResources.contains(svg)) {
        SDL_IOStream* rw = SDL_IOFromConstMem(svg.c_str(), svg.size());
        SDL_Surface* surface = IMG_Load_IO(rw, 1);
        std::shared_ptr<SDL_Texture> texture = MakeSharedTexture(renderer, surface);
        m_TextureResources.insert({svg, texture});

        SDL_DestroySurface(surface);
    }

    return m_TextureResources[svg];
}

std::shared_ptr<SDL_Texture> ResourceManager::MakeSharedTexture(SDL_Renderer* renderer, SDL_Surface* surface) {
    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(renderer, surface);

    if (nullptr == pTexture) {
        SDL_Log("Could not load texture from surface");
    }

    return {pTexture, TextureFunctorDeleter()};
}