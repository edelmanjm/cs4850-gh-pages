#include <ResourceManager.h>

ResourceManager& ResourceManager::Instance() {
    static ResourceManager instance;
    return instance;
}

std::shared_ptr<SDL_Texture> ResourceManager::LoadTexture(SDL_Renderer* renderer, std::string filepath)  {
    if (!m_TextureResources.contains(filepath)) {
        SDL_Surface* pixels = SDL_LoadBMP(filepath.c_str());
        SDL_SetSurfaceColorKey(pixels, SDL_TRUE, SDL_MapRGB(pixels->format, 0xFF, 0, 0xFF));
        std::shared_ptr<SDL_Texture> texture = MakeSharedTexture(renderer, pixels);
        m_TextureResources.insert({filepath, texture});

        SDL_DestroySurface(pixels);
        SDL_Log("Created new resource %s", filepath.c_str());
    } else {
        SDL_Log("Reused resource %s", filepath.c_str());
    }

    return m_TextureResources[filepath];
}

std::shared_ptr<SDL_Texture> ResourceManager::MakeSharedTexture(SDL_Renderer* renderer, SDL_Surface* pixels) {
    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(renderer, pixels);

    if (nullptr == pTexture) {
        SDL_Log("Could not load texture from surface");
    }

    return {pTexture, TextureFunctorDeleter()};
}