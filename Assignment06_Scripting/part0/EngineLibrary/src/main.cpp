// Linux: g++ -std=c++20 main.cpp -o prog `pkg-config --libs sdl3`
#include <Application.h>

int main(int argc, char* argv[]){

    Application app(argc, argv);
    app.Loop(120.0f);

    return 0;
}
