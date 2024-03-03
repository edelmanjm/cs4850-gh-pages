#include <Scene.h>
#include <components/InputComponent.h>

Scene::Scene(SDL_Renderer* renderer, uint32_t width) : m_Renderer(renderer) {
    // Initialize all the enemies
    int row = 1;
    int column = 1;
    for (int i = 0; i < 36; i++) {
        std::shared_ptr<EnemyEntity> e = std::make_shared<EnemyEntity>(m_Renderer);
        e->AddRequiredComponents(m_Renderer);

        // Calculate position for our enemy
        if (i % 12 == 0) {
            ++row;
            column = 0;
        }
        column++;

        e->GetTransform()->SetXY(column * 40 + 80, row * 40);

        m_Enemies.push_back(std::move(e));
    }

    m_MainCharacter = std::make_shared<PlayerGameEntity>(m_Renderer);
    m_MainCharacter->AddRequiredComponents(m_Renderer, width);
    m_MainCharacter->GetTransform()->SetXY(640.0 / 2 - (32.0 / 2), 440);
}

Scene::~Scene() = default;

void Scene::Input(float deltaTime) {
    // Handle SDL_GetKeyboardState after -- your SDL_PollEvent
    m_MainCharacter->Input(deltaTime);
}

void Scene::Update(float deltaTime) {
    // Update our main character
    m_MainCharacter->Update(deltaTime);

    // Updating all of our enemies
    for (const auto& enemy : m_Enemies) {
        enemy->Update(deltaTime);

        bool enemyIsHit = enemy->Intersects(m_MainCharacter->GetProjectile());

        bool gameOver = false;

        if (enemyIsHit && enemy->IsRenderable()) {
            enemy->SetRenderable(false);
            m_Points += 10.0f;
            SDL_Log("Your score is %f", m_Points);
//            SDL_Log("Enemy was %i was removed", i);
        }
        if (enemy->IsRenderable()) {
            gameOver = m_MainCharacter->Intersects(enemy->GetProjectile());
        }

        if (gameOver) {
            SDL_Log("YOU LOOOOOOOOOSE!");
            SDL_Log("Your score is %f", m_Points);
//            SDL_Log("Enemy %i got you. enemy[i].IsRenderable()=%i | Projectile: %i", i, enemies[i]->IsRenderable(),
//                    enemies[i]->GetProjectile()->IsRenderable());
            m_SceneIsActive = false;
        }

        if (m_Points >= m_Enemies.size() * 10.0f) {
            SDL_Log("You win!");
            m_SceneIsActive = false;
        }
    }
}

void Scene::Render() {
    SDL_SetRenderDrawColor(m_Renderer, 32, 32, 64, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(m_Renderer);

    SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    // Render our enemies
    for (int i = 0; i < m_Enemies.size(); i++) {
        m_Enemies[i]->Render(m_Renderer);
    }
    // Render our main character
    m_MainCharacter->Render(m_Renderer);

    SDL_RenderPresent(m_Renderer);
}

void Scene::SetSceneActiveStatus(bool status) { m_SceneIsActive = status; }

bool Scene::IsSceneActive() const { return m_SceneIsActive; }
