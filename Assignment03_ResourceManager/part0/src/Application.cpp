#include <Application.h>

Application::Application(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    }

    // Create our window
    m_Window = SDL_CreateWindow("An SDL3 Window", m_Width, m_Height,
                                SDL_WINDOW_METAL);
    m_Renderer = SDL_CreateRenderer(m_Window, nullptr, SDL_RENDERER_ACCELERATED);
    if (nullptr == m_Renderer) {
        SDL_Log("Error creating renderer");
    }

    // Initialize all the m_Enemies
    uint32_t row = 1;
    uint32_t column = 1;
    for (int i = 0; i < 36; i++) {
        Sprite sp;
        sp.CreateSprite(m_Renderer, "../assets/enemy.bmp");

        if (i % 12 == 0) {
            ++row;
            column = 0;
        }
        sp.Move(static_cast<float>(column * 40 + 80), static_cast<float>(row * 40));
        column++;
        std::unique_ptr<EnemyEntity> e = std::make_unique<EnemyEntity>(m_Renderer, sp);
        m_Enemies.push_back(std::move(e));
    }

    Sprite characterSprite;
    characterSprite.CreateSprite(m_Renderer, "../assets/hero.bmp");
    characterSprite.Move(640.0 / 2 - (32.0 / 2), 440);
    m_MainCharacter = std::make_unique<PlayerGameEntity>(m_Renderer, characterSprite, 0, static_cast<float>(m_Width) -
                                                                                         characterSprite.GetRectangle().w);
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
            m_Run = false;
        } else if (event.type == SDL_EVENT_KEY_DOWN) {
//                SDL_Log("Some key was pressed down");
//                SDL_Log("%u",event.key.keysym.sym);
//                if(event.key.keysym.sym == SDLK_0){
//                    SDL_Log("0 was pressed");
//                }
        }
    }

    // Handle SDL_GetKeyboardState after -- your SDL_PollEvent
    m_MainCharacter->Input(deltaTime);
}

void Application::Update(float deltaTime) {
    // Updating all of our m_Enemies
    for (const auto &enemy: m_Enemies) {
        enemy->Update(deltaTime);

        bool enemyIsHit = enemy->Intersects(m_MainCharacter->GetProjectile());

        bool GameOver = m_MainCharacter->Intersects(enemy->GetProjectile());
        if (enemyIsHit && enemy->IsRenderable()) {
            enemy->SetRenderable(false);
            m_Points += 10.0f;
            SDL_Log("Your score is %f", m_Points);
        }

        if (GameOver) {
            SDL_Log("YOU LOOOOOOOOOSE!");
            SDL_Log("Your score is %f", m_Points);
            m_Run = false;
        }
    }
    // Update our main character
    m_MainCharacter->Update(deltaTime);
}

void Application::Render() {
    SDL_SetRenderDrawColor(m_Renderer, 0, 64, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(m_Renderer);

    SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    // Render our m_Enemies
    for (const auto &enemy: m_Enemies) {
        enemy->Render(m_Renderer);
    }
    // Render our main character
    m_MainCharacter->Render(m_Renderer);

    SDL_RenderPresent(m_Renderer);
}

void Application::Loop(float targetFPS) {
    // Our infinite game/application loop

    uint32_t lastTime, currentTime;

    // Record our 'starting time'
    lastTime = SDL_GetTicks();
    uint32_t framesElapsed = 0;
    float deltaTime = 1.0f / targetFPS;
    while (m_Run) {
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