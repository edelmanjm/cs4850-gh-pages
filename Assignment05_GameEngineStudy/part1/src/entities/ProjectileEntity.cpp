#include <components/Collision2DComponent.h>
#include <components/TextureComponent.h>
#include <entities/ProjectileEntity.h>

ProjectileEntity::ProjectileEntity() {
    timeSinceLastLaunch = SDL_GetTicks();
    SetRenderable(false);
}

void ProjectileEntity::AddRequired(SDL_Renderer* renderer) {
    GameEntity::AddRequired();

    std::shared_ptr<TextureComponent> texture = std::make_shared<TextureComponent>();
    texture->CreateTextureComponent(renderer, "../assets/rocket.bmp");
    AddComponent(texture);

    std::shared_ptr<Collision2DComponent> col = std::make_shared<Collision2DComponent>();
    AddComponent(col);
}

void ProjectileEntity::Launch(float x, float y, float speed, uint64_t minLaunchTime) {
    m_Speed = speed;
    if (SDL_GetTicks() - timeSinceLastLaunch > minLaunchTime) {
        auto transform = GetComponent<TransformComponent>(ComponentType::TransformComponent).value();
        auto col = GetComponent<Collision2DComponent>(ComponentType::Collision2DComponent).value();
        transform->SetXY(x, y);
        col->SetXY(x, y);

        timeSinceLastLaunch = SDL_GetTicks();
        m_IsFiring = true;

        SetRenderable(true);
    }
}

void ProjectileEntity::Input(float deltaTime) {
    for (auto &[key, value]: m_Components) {
        m_Components[key]->Input(deltaTime);
    }
}

void ProjectileEntity::Update(float deltaTime) {
    auto transform = GetComponent<TransformComponent>(ComponentType::TransformComponent).value();

    if (m_IsFiring) {
        SetRenderable(true);
        transform->SetY(transform->GetY() + m_Speed * deltaTime);
    } else {
        SetRenderable(false);
    }

    if (transform->GetY() < 0.0f || transform->GetY() > 480.0f) {
        m_IsFiring = false;
    }

    for (auto &[key, value]: m_Components) {
        m_Components[key]->Update(deltaTime);
    }
}