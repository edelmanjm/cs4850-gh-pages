#include <Application.h>
#include <components/Collision2DComponent.h>
#include <components/LifetimeComponent.h>
#include <components/TransformWrappingComponent.h>
#include <scenes/PythonScene.h>

int main(int argc, char* argv[]) {
    int w = 640;
    int h = 480;
    auto renderer = std::make_shared<Renderer>(w, h);
    auto scene = std::make_shared<PythonScene>(renderer);
    scene->SetOnUpdate([scene, w, h](auto dt) {
        if (rand() % 10 == 0) {
            auto projectile = std::make_shared<CollidingRectangleEntity>();
            projectile->AddRequired(h2d::FRect(-2, -2, 2, 2));
            projectile->AddComponent(std::make_shared<TransformWrappingComponent>(h2d::FRect(0, 0, w, h)));
            projectile->AddComponent(std::make_shared<LifetimeComponent>(1000));
            projectile->GetTransform()->m_Transform = h2d::Homogr().setTranslation(w / 2, h / 2);
            projectile->m_VelocityX = 10;
            projectile->m_VelocityY = 10;

            scene->AddEntity(projectile);
        }
    });



    Application app(renderer);
    app.setScene(scene);
    app.Loop(120.0f);

    return 0;
}