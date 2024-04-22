#include <SDL3_image/SDL_image.h>
#define NSVG_EXPORT static
#define NANOSVG_IMPLEMENTATION
#include <nanosvg.h>
#define NANOSVGRAST_IMPLEMENTATION
#include <nanosvgrast.h>

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

std::shared_ptr<SDL_Texture> ResourceManager::LoadSvg(SDL_Renderer* renderer, const std::string& svg, float scale) {
    if (!m_TextureResources.contains(svg)) {
        SDL_IOStream* rw = SDL_IOFromConstMem(svg.c_str(), svg.size());
        SDL_Surface* surface = LoadScaledSvg(rw, scale);
        std::shared_ptr<SDL_Texture> texture = MakeSharedTexture(renderer, surface);
        m_TextureResources.insert({svg, texture});

        SDL_DestroySurface(surface);
    }

    return m_TextureResources[svg];
}

std::shared_ptr<SDL_Texture> ResourceManager::LoadImage(SDL_Renderer *renderer, const std::string &filepath) {
    if (!m_TextureResources.contains(filepath)) {
        SDL_Surface* surface = IMG_Load(filepath.c_str());
        std::shared_ptr<SDL_Texture> texture = MakeSharedTexture(renderer, surface);
        m_TextureResources.insert({filepath, texture});

        SDL_DestroySurface(surface);
    }

    return m_TextureResources[filepath];
}

std::shared_ptr<SDL_Texture> ResourceManager::MakeSharedTexture(SDL_Renderer* renderer, SDL_Surface* surface) {
    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(renderer, surface);

    if (nullptr == pTexture) {
        SDL_Log("Could not load texture from surface");
    }

    return {pTexture, TextureFunctorDeleter()};
}

SDL_Surface* ResourceManager::LoadScaledSvg(SDL_IOStream *src, float scale) {
    char *data;
    struct NSVGimage *image;
    struct NSVGrasterizer *rasterizer;
    SDL_Surface *surface = nullptr;

    data = (char *)SDL_LoadFile_IO(src, nullptr, SDL_FALSE);
    if (!data) {
        return nullptr;
    }

    /* For now just use default units of pixels at 96 DPI */
    image = nsvgParse(data, "px", 96.0f);
    SDL_free(data);
    if (!image || image->width <= 0.0f || image->height <= 0.0f) {
        IMG_SetError("Couldn't parse SVG image");
        return nullptr;
    }

    rasterizer = nsvgCreateRasterizer();
    if (!rasterizer) {
        IMG_SetError("Couldn't create SVG rasterizer");
        nsvgDelete(image);
        return nullptr;
    }

    surface = SDL_CreateSurface((int)SDL_ceilf(image->width * scale),
                                (int)SDL_ceilf(image->height * scale),
                                SDL_PIXELFORMAT_RGBA32);

    if (!surface) {
        nsvgDeleteRasterizer(rasterizer);
        nsvgDelete(image);
        return nullptr;
    }

    nsvgRasterize(rasterizer, image, 0.0f, 0.0f, scale, (unsigned char *)surface->pixels, surface->w, surface->h, surface->pitch);
    nsvgDeleteRasterizer(rasterizer);
    nsvgDelete(image);

    return surface;
}