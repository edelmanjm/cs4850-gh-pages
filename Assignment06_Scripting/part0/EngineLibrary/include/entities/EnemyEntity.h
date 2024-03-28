#pragma once

#include <entities/GameEntity.h>
#include <entities/ProjectileEntity.h>

class EnemyEntity : public GameEntity {

private:
    bool m_XPositiveDirection{true};
    float m_Offset{0.0f};
    float m_Speed{100.0f};
    uint64_t m_MinLaunchTime{5000};

public:
    explicit EnemyEntity();
    ~EnemyEntity() override = default;
    void AddRequired(SDL_FRect transform, SDL_Renderer* renderer);

    void Update(float deltaTime) override;
    void Render(SDL_Renderer* renderer) override;

    [[nodiscard]] virtual std::shared_ptr<ProjectileEntity> GetProjectile() const;
};