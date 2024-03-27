#include <Application.h>
#include <components/Collision2DComponent.h>
#include <scenes/SpaceInvaders.h>

Application::Application(SDL_Renderer* renderer) : m_Renderer(renderer) {}

Application::~Application() {
    SDL_DestroyWindow(SDL_GetRenderWindow(m_Renderer));
    SDL_Quit();
}

void Application::Input(float deltaTime) {
    if (!m_Scene) {
        SDL_Log("No scene is set for the application");
        return;
    }

    SDL_Event event;
    // Processing input
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            SDL_Log("Program quit %llu", event.quit.timestamp);
            m_Scene.value()->m_SceneIsActive = false;
        } else if (event.type == SDL_EVENT_KEY_DOWN) {
            //                SDL_Log("Some key was pressed down");
            //                SDL_Log("%u",event.key.keysym.sym);
            //                if(event.key.keysym.sym == SDLK_0){
            //                    SDL_Log("0 was pressed");
            //                }
        }
    }

    // Handle SDL_GetKeyboardState after -- your SDL_PollEvent
    m_Scene.value()->Input(deltaTime);
}

void Application::Update(float deltaTime) {
    if (!m_Scene) {
        SDL_Log("No scene is set for the application");
        return;
    }

    m_Scene.value()->Update(deltaTime);
}

void Application::Render() {
    if (!m_Scene) {
        SDL_Log("No scene is set for the application");
        return;
    }

    m_Scene.value()->Render();
}

void Application::Loop(float targetFPS) {
    // Our infinite game/application loop

    uint32_t lastTime, currentTime;

    // Record our 'starting time'
    lastTime = SDL_GetTicks();
    uint32_t framesElapsed = 0;
    float deltaTime = 1.0f / targetFPS;
    // Loop until the scene is set and the scene has ended
    while (!m_Scene || m_Scene.value()->m_SceneIsActive) {
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


SDL_Renderer* Application::createRenderer(int w, int h) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    }

    // Create our window
    auto* window = SDL_CreateWindow("An SDL3 Window", w, h, SDL_WINDOW_OPENGL);
    auto* renderer = SDL_CreateRenderer(window, nullptr, SDL_RENDERER_ACCELERATED);
    if (nullptr == renderer) {
        SDL_Log("Error creating renderer");
    }

    return renderer;
}

void Application::setScene(const std::shared_ptr<Scene>& scene) {
    m_Scene = scene;
    m_Scene->get()->m_SceneIsActive = true;
}
