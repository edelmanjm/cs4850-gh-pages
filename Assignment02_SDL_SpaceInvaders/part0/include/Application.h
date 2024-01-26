// Application.h
#pragma once

#include <SDL3/SDL.h>
#include <cstdlib>
#include <vector>
#include <memory>

class Sprite {

private:
    SDL_FRect m_Rectangle{20.0f, 20.0f, 32.0f, 32.0f};
    SDL_Texture* m_Texture;

public:
    Sprite() = default;
    ~Sprite() = default;
//        TODO: We'll want a resource manager to handle this.
//        SDL_DestroyTexture(m_Texture);

    void CreateSprite(SDL_Renderer *renderer, const char *filepath) {
        SDL_Surface *pixels = SDL_LoadBMP(filepath);
        SDL_SetSurfaceColorKey(pixels, SDL_TRUE, SDL_MapRGB(pixels->format, 0xFF, 0, 0xFF));

        m_Texture = SDL_CreateTextureFromSurface(renderer, pixels);
        if (nullptr == m_Texture) {
            SDL_Log("Could not load texture from surface");
        }

        SDL_DestroySurface(pixels);
    }

    void Update(float deltaTime) {
    }

    void Render(SDL_Renderer *renderer) {
        if (nullptr == m_Texture) {
            SDL_RenderRect(renderer, &m_Rectangle);
        } else {
            SDL_RenderTexture(renderer, m_Texture, nullptr, &m_Rectangle);
        }
    }

    void SetW(float w) {
        m_Rectangle.w = w;
    }

    void SetX(float x) {
        m_Rectangle.x = x;
    }

    void SetY(float y) {
        m_Rectangle.y = y;
    }

    [[nodiscard]] float GetX() const {
        return m_Rectangle.x;
    }

    [[nodiscard]] float GetY() const {
        return m_Rectangle.y;
    }

    void Move(float x, float y) {
        m_Rectangle.x = x;
        m_Rectangle.y = y;
    }

    [[nodiscard]] SDL_FRect GetRectangle() const {
        return m_Rectangle;
    }
};


class GameEntity {

protected:
    Sprite m_Sprite;
    bool m_Renderable{true};

public:
    explicit GameEntity(Sprite sprite) {
        m_Sprite = sprite;
    }

    virtual ~GameEntity() = default;

    virtual void Input(float deltaTime) {
    }

    virtual void Update(float deltaTime) {
    }

    virtual void Render(SDL_Renderer *renderer) {
    }

    void SetRenderable(bool value) {
        m_Renderable = value;
    }

    [[nodiscard]] bool IsRenderable() const;

    bool Intersects(const std::shared_ptr<GameEntity>& e) {
        SDL_FRect source = e->m_Sprite.GetRectangle();
        SDL_FRect us = m_Sprite.GetRectangle();
        SDL_FRect result;
        return SDL_GetRectIntersectionFloat(&source, &us, &result);
    }
};

bool GameEntity::IsRenderable() const {
    return m_Renderable;
}

class Projectile : public GameEntity {

private:
    float m_Speed{200.0f};
    bool m_IsFiring{false};
    bool m_YDirectionUp{true};
    uint64_t timeSinceLastLaunch;

public:
    explicit Projectile(Sprite sprite) : GameEntity(sprite) {
        timeSinceLastLaunch = SDL_GetTicks();
        m_Renderable = false;
    }

    void Launch(float x, float y, bool yDirectionIsUp, uint64_t minLaunchTime = 3000) {
        if (SDL_GetTicks() - timeSinceLastLaunch > minLaunchTime) {
            timeSinceLastLaunch = SDL_GetTicks();
            m_IsFiring = true;
            m_YDirectionUp = yDirectionIsUp;
            m_Sprite.Move(x, y);
        }
    }

    void Update(float deltaTime) override {
        if (m_IsFiring) {
            m_Renderable = true;
            if (m_YDirectionUp) {
                m_Sprite.SetY(m_Sprite.GetY() - m_Speed * deltaTime);
            } else {
                m_Sprite.SetY(m_Sprite.GetY() + m_Speed * deltaTime);
            }
        } else {
            m_Renderable = false;
        }

        if (m_Sprite.GetY() < 0.0f || m_Speed > 480.0f) {
            m_IsFiring = false;
        }
    }

    void Render(SDL_Renderer *renderer) override {
        if (m_Renderable) {
            m_Sprite.Render(renderer);
        } else {
            // Do nothing;
        }
    }
};

class EnemyGameEntity : public GameEntity {

private:
    std::shared_ptr<Projectile> m_Projectile;
    bool m_XPositiveDirection{true};
    float m_Offset{0.0f};
    float m_Speed{100.0f};
    uint64_t m_MinLaunchTime{5000};

public:
    EnemyGameEntity(SDL_Renderer *renderer, Sprite sprite) : GameEntity(sprite) {
        Sprite sp;
        sp.CreateSprite(renderer, "../assets/rocket.bmp");
        sp.SetW(24.0f);
        m_Projectile = std::make_shared<Projectile>(sp);

        // Set a random launch time for the m_Enemies
        m_MinLaunchTime += std::rand() % 10000;
    }

    ~EnemyGameEntity() override = default;

    void Input(float deltaTime) override {
    }

    void Update(float deltaTime) override {
        m_Projectile->Update(deltaTime);
        if (m_Offset > 80) {
            m_XPositiveDirection = false;
        }
        if (m_Offset < -80) {
            m_XPositiveDirection = true;
        }

        if (m_XPositiveDirection) {
            m_Sprite.SetX(m_Sprite.GetX() + m_Speed * deltaTime);
            m_Offset += m_Speed * deltaTime;
        } else {
            m_Sprite.SetX(m_Sprite.GetX() - m_Speed * deltaTime);
            m_Offset -= m_Speed * deltaTime;
        }

        if (m_Renderable) {
            m_Projectile->Launch(m_Sprite.GetX(), m_Sprite.GetY(), false, m_MinLaunchTime);
        }
    }

    void Render(SDL_Renderer *renderer) override {
        if (m_Renderable) {
            m_Projectile->Render(renderer);
            m_Sprite.Render(renderer);
        } else {
            // Do nothing;
        }
    }

    [[nodiscard]] virtual std::shared_ptr<Projectile> GetProjectile() const {
        return m_Projectile;
    }
};


class PlayerGameEntity : public GameEntity {

private:
    float m_Speed{150.0f};
    std::shared_ptr<Projectile> m_Projectile;

public:
    PlayerGameEntity(SDL_Renderer *renderer, Sprite sprite) : GameEntity(sprite) {
        Sprite sp;
        sp.CreateSprite(renderer, "../assets/rocket.bmp");
        sp.SetW(24.0f);
        m_Projectile = std::make_shared<Projectile>(sp);
    }

    ~PlayerGameEntity() override = default;

    void Input(float deltaTime) override {
        const Uint8 *state = SDL_GetKeyboardState(nullptr);
        if (state[SDL_SCANCODE_LEFT]) {
            m_Sprite.SetX(m_Sprite.GetX() - m_Speed * deltaTime);
        } else if (state[SDL_SCANCODE_RIGHT]) {
            m_Sprite.SetX(m_Sprite.GetX() + m_Speed * deltaTime);
        }

        if (state[SDL_SCANCODE_UP]) {
            SDL_Log("Launching!");
            m_Projectile->Launch(m_Sprite.GetX(), m_Sprite.GetY(), true);
        }
    }

    void Update(float deltaTime) override {
        m_Projectile->Update(deltaTime);
    }

    void Render(SDL_Renderer *renderer) override {
        m_Projectile->Render(renderer);
        m_Sprite.Render(renderer);
    }

    [[nodiscard]] virtual std::shared_ptr<Projectile> GetProjectile() const {
        return m_Projectile;
    }
};

class Application {

private:
    // Enemy sprites
    std::vector<std::unique_ptr<EnemyGameEntity>> m_Enemies;
    // Main Character
    std::unique_ptr<PlayerGameEntity> m_MainCharacter;

    bool m_Run{true};
    float m_Points{0.0f};
    SDL_Window* m_Window;
    SDL_Renderer *m_Renderer;

public:
    Application(int argc, char *argv[]) {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
            SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        }
        // Create our window
        m_Window = SDL_CreateWindow("An SDL3 Window", 640, 480,
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
            std::unique_ptr<EnemyGameEntity> e = std::make_unique<EnemyGameEntity>(m_Renderer, sp);
            m_Enemies.push_back(std::move(e));
        }

        Sprite characterSprite;
        characterSprite.CreateSprite(m_Renderer, "../assets/hero.bmp");
        characterSprite.Move(640.0 / 2 - (32.0 / 2), 440);
        m_MainCharacter = std::make_unique<PlayerGameEntity>(m_Renderer, characterSprite);
    }

    ~Application() {
        SDL_DestroyWindow(m_Window);
        SDL_Quit();
    }

    void Input(float deltaTime) {
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

    void Update(float deltaTime) {
        // Updating all of our m_Enemies
        for (const auto & enemy : m_Enemies) {
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

    void Render() {
        SDL_SetRenderDrawColor(m_Renderer, 0, 64, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(m_Renderer);

        SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        // Render our m_Enemies
        for (const auto & enemy : m_Enemies) {
            enemy->Render(m_Renderer);
        }
        // Render our main character
        m_MainCharacter->Render(m_Renderer);

        SDL_RenderPresent(m_Renderer);
    }

    void Loop(float targetFPS) {
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
};
