#pragma once

#include <entities/GameEntity.h>
#include <entities/ProjectileEntity.h>

class EnemyEntity : public GameEntity {

private:
    bool m_XPositiveDirection{true};
    double m_Offset{0.0};
    double m_Speed{100.0};
    uint64_t m_MinLaunchTime{5000};

public:
    explicit EnemyEntity();
    ~EnemyEntity() override = default;
    void AddRequired(h2d::FRect dims, SDL_Renderer* renderer);

    void Update(float deltaTime) override;
    void Render(SDL_Renderer* renderer) override;

    [[nodiscard]] virtual std::shared_ptr<ProjectileEntity> GetProjectile() const;
};