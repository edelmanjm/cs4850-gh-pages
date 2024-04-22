#include <Renderer.h>

Renderer::Renderer(int w, int h) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    }

    // Create our window
    auto* window = SDL_CreateWindow("An SDL3 Window", w, h, SDL_WINDOW_OPENGL);
    m_Wrapped = SDL_CreateRenderer(window, nullptr, 0);
    if (nullptr == m_Wrapped) {
        SDL_Log("Error creating renderer");
    }
}