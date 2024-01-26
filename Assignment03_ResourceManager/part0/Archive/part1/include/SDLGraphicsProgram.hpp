#ifndef SDLGRAPHICSPROGRAM_HPP
#define SDLGRAPHICSPROGRAM_HPP

// ==================== Libraries ==================
// Depending on the operating system we use
// The paths to SDL are actually different.
// The #define statement should be passed in
// when compiling using the -D argument.
// This gives an example of how a programmer
// may support multiple platforms with different
// dependencies.
//
// Note that your path may be different depending on where you intalled things
//
//
#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // This works for Mac
    #include <SDL.h>
#endif

#include "Sprite.hpp"

#include <vector>

// This class sets up a full graphics program
class SDLGraphicsProgram{
public:
    // Constructor
    SDLGraphicsProgram(int w, int h);
    // Desctructor
    ~SDLGraphicsProgram();
    // Startup Routine
    void StartUp();
    // Per frame update
    void Update();
    // Renders shapes to the screen
    void Render();
    // loop that runs forever
    void Loop();
    // Get Pointer to Window
    SDL_Window* GetSDLWindow();
    // Get Pointer to Renderer
    SDL_Renderer* GetSDLRenderer();

private:
    // Characters in our game
    std::vector<Sprite> mSprites;

    // Screen dimension constants
    int             mScreenHeight;
    int             mScreenWidth;
    // The window we'll be rendering to
    SDL_Window*     mWindow     = nullptr;
    SDL_Renderer*   mRenderer   = nullptr;
};

#endif
