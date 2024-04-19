// Linux: g++ -std=c++20 main.cpp -o prog `pkg-config --libs sdl3`
#include <Application.h>
#include <scenes/Scene.h>
#include <scenes/SpaceInvaders.h>

int main(int argc, char* argv[]){

    int w = 640;
    int h = 480;
    auto renderer = std::make_shared<Renderer>(w, h);
    auto scene = std::make_shared<SpaceInvaders>(renderer->m_Wrapped, w);
    Application app(renderer);
    app.setScene(scene);
    app.Loop(120.0f);

    return 0;
}
