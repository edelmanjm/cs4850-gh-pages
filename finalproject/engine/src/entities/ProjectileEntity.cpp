#include <ResourceManager.h>
#include <components/Collision2DComponent.h>
#include <components/TextureComponent.h>
#include <entities/ProjectileEntity.h>
#include <utility/Geometry.h>

ProjectileEntity::ProjectileEntity() {
    timeSinceLastLaunch = SDL_GetTicks();
    m_Renderable = false;
}

void ProjectileEntity::AddRequired(h2d::FRect dims, SDL_Renderer* renderer) {
    GameEntity::AddRequired();

    std::shared_ptr<TextureComponent> texture =
        std::make_shared<TextureComponent>(ResourceManager::Instance().LoadTexture(renderer, "../assets/rocket.bmp"),
                                           dims);
    AddComponent(texture);

    std::shared_ptr<Collision2DComponent> col = std::make_shared<Collision2DComponent>(dims);
    AddComponent(col);
}

void ProjectileEntity::Launch(float x, float y, float speed, uint64_t minLaunchTime) {
    m_Speed = speed;
    if (SDL_GetTicks() - timeSinceLastLaunch > minLaunchTime) {
        auto transform = GetComponent<TransformComponent>(ComponentType::TransformComponent).value();
        auto col = GetComponent<Collision2DComponent>(ComponentType::Collision2DComponent).value();
        transform->m_Transform.setTranslation(x, y);

        timeSinceLastLaunch = SDL_GetTicks();
        m_IsFiring = true;

        m_Renderable = true;
    }
}

void ProjectileEntity::Input(float deltaTime) {
    for (auto &[key, value]: m_Components) {
        m_Components[key]->Input(deltaTime);
    }
}

void ProjectileEntity::Update(float deltaTime) {
    auto& transform = GetComponent<TransformComponent>(ComponentType::TransformComponent).value()->m_Transform;

    if (m_IsFiring) {
        m_Renderable = true;
        transform.addTranslation(0.0, m_Speed * deltaTime);
    } else {
        m_Renderable = false;
    }

    auto transformed = GetTransformedOrigin();
    if (transformed.getY() < 0.0 || transformed.getY() > 480.0f) {
        m_IsFiring = false;
    }

    for (auto &[key, value]: m_Components) {
        m_Components[key]->Update(deltaTime);
    }
}