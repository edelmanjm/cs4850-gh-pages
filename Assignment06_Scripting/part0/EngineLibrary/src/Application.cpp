#include <Application.h>
#include <components/Collision2DComponent.h>
#include <components/InputComponent.h>
#include <components/TextureComponent.h>
#include <entities/EnemyEntity.h>

Application::Application(int w, int h) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    }

    // Create our window
    m_Window = SDL_CreateWindow("An SDL3 Window", w, h, SDL_WINDOW_OPENGL);
    m_Renderer = SDL_CreateRenderer(m_Window, nullptr, SDL_RENDERER_ACCELERATED);
    m_Scene = std::make_unique<Scene>(m_Renderer, w);
    m_Scene->SetSceneActiveStatus(true);
    if (nullptr == m_Renderer) {
        SDL_Log("Error creating renderer");
    }
}

Application::~Application() {
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}

void Application::Input(float deltaTime) {
    SDL_Event event;
    // Processing input
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            SDL_Log("Program quit %llu", event.quit.timestamp);
            m_Scene->SetSceneActiveStatus(false);
        } else if (event.type == SDL_EVENT_KEY_DOWN) {
            //                SDL_Log("Some key was pressed down");
            //                SDL_Log("%u",event.key.keysym.sym);
            //                if(event.key.keysym.sym == SDLK_0){
            //                    SDL_Log("0 was pressed");
            //                }
        }
    }

    // Handle SDL_GetKeyboardState after -- your SDL_PollEvent
    m_Scene->Input(deltaTime);
}

void Application::Update(float deltaTime) {
    m_Scene->Update(deltaTime);
}

void Application::Render() {
    m_Scene->Render();
}

void Application::Loop(float targetFPS) {
    // Our infinite game/application loop

    uint32_t lastTime, currentTime;

    // Record our 'starting time'
    lastTime = SDL_GetTicks();
    uint32_t framesElapsed = 0;
    float deltaTime = 1.0f / targetFPS;
    while (m_Scene->IsSceneActive()) {
        uint64_t startOfFrame = SDL_GetTicks();
        // We want, input/update/render to take 16ms
        Input(deltaTime);
        Update(deltaTime);
        Render();
        uint32_t elapsedTime = SDL_GetTicks() - startOfFrame;
        framesElapsed++;

        // Time keeping code - for frames elapsed
        currentTime = SDL_GetTicks();
        // Insert a 'frame cap' so that our program
        // does not run too fast.
        if (float(elapsedTime) < (1000 / targetFPS)) {
            uint32_t delay = static_cast<uint32_t>(1000 / targetFPS) - elapsedTime;
            SDL_Delay(delay);
            //                SDL_Log("elaspedTime: %li",elapsedTime);
            //                SDL_Log("delaying by: %li",delay);
        }
        // If 1 second passes,              m_Enemies[i]->report how many frames
        // have been executed.
        if (currentTime > lastTime + 1000) {
            SDL_Log("1 second has elapsed");
            SDL_Log("%u", framesElapsed);
            deltaTime = 1.0f / float(framesElapsed);
            framesElapsed = 0;
            lastTime = SDL_GetTicks();
        }
    }
}