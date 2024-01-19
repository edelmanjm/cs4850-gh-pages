#ifndef SDLGRAPHICSPROGRAM
#define SDLGRAPHICSPROGRAM

// ==================== Libraries ==================
// Depending on the operating system we use
// The paths to SDL are actually different.
// The #define statement should be passed in
// when compiling using the -D argument.
// This gives an example of how a programmer
// may support multiple platforms with different
// dependencies.
#if defined(LINUX) || defined(MINGW)
	#include <SDL2/SDL.h>
#else
	// Windows and Mac use a different path
	// If you have compilation errors, change this as needed.
	#include <SDL.h>
#endif

// Forward declare 'Rectangle'
// Because we have a pointer to 'mRectangles' in SDLGraphicsProgram
// this is better and avoids a dependency.
// Compilation speed will be much faster as well.
class Rectangle;

// This class sets up a full graphics program
class SDLGraphicsProgram{
public:

    // Constructor
    SDLGraphicsProgram(int w, int h);
    // Desctructor
    ~SDLGraphicsProgram();
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
    // Number of blocks to render in this simulation
    static constexpr unsigned int mBlocks = 500;
    // Create our array of rectangles!
    Rectangle* mRectangles;

    // Screen dimension constants
    int mScreenHeight;
    int mScreenWidth;
    // The window we'll be rendering to
    SDL_Window* mWindow ;
    // SDL Renderer
    SDL_Renderer* mRenderer = NULL;
};

#endif
