#include <components/InputComponent.h>
#include <entities/invaders/PlayerGameEntity.h>
#include <scenes/SpaceInvaders.h>

SpaceInvaders::SpaceInvaders(SDL_Renderer* renderer, uint32_t width) : Scene(renderer) {
    // Initialize all the enemies
    int row = 1;
    int column = 1;
    for (int i = 0; i < 36; i++) {
        std::shared_ptr<EnemyEntity> e = std::make_shared<EnemyEntity>();
        e->AddRequired({0.0f, 0.0f, 32.0f, 32.0f}, m_Renderer);

        // Calculate position for our enemy
        if (i % 12 == 0) {
            ++row;
            column = 0;
        }
        column++;

        e->GetTransform()->m_Transform.setTranslation(column * 40 + 80, row * 40);

        m_Enemies.push_back(std::move(e));
    }

    m_MainCharacter = std::make_shared<PlayerGameEntity>();
    m_MainCharacter->AddRequired({0.0f, 0.0f, 32.0f, 32.0f}, m_Renderer, width);
    m_MainCharacter->GetTransform()->m_Transform.setTranslation(640.0 / 2 - (32.0 / 2), 440.0);
}

SpaceInvaders::~SpaceInvaders() = default;

void SpaceInvaders::Input(float deltaTime) {
    // Handle SDL_GetKeyboardState after -- your SDL_PollEvent
    m_MainCharacter->Input(deltaTime);
}

void SpaceInvaders::Update(float deltaTime) {
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
            //            SDL_Log("Enemy %i got you. enemy[i].IsRenderable()=%i | Projectile: %i", i,
            //            enemies[i]->IsRenderable(),
            //                    enemies[i]->GetProjectile()->IsRenderable());
            m_SceneIsActive = false;
        }

        if (m_Points >= m_Enemies.size() * 10.0f) {
            SDL_Log("You win!");
            m_SceneIsActive = false;
        }
    }
}

void SpaceInvaders::Render() {
    SDL_SetRenderDrawColor(m_Renderer, 32, 32, 64, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(m_Renderer);

    SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    // Render our enemies
    for (const auto& m_Enemy : m_Enemies) {
        m_Enemy->Render(m_Renderer);
    }
    // Render our main character
    m_MainCharacter->Render(m_Renderer);

    SDL_RenderPresent(m_Renderer);
}

void SpaceInvaders::AddEntity(const std::shared_ptr<GameEntity>& entity) {
    entity->m_ParentScene = shared_from_this();
}

void SpaceInvaders::RemoveEntity(std::shared_ptr<GameEntity> entity) {

}