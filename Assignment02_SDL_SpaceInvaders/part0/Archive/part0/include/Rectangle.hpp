#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

// Note: If you want SDL to build on multiple platforms, for now
//       this is the easiest solutoin to get SDL building on multiple
//       paths for this class.
//       A better solution is to use sdl-config --cflags --libs in the
//       build system.
#if defined(LINUX) || defined(MINGW)
	#include <SDL2/SDL.h>
#else
	// Windows and Mac use a different path
	// If you have compilation errors, change this as needed.
	#include <SDL.h>
#endif

class Rectangle{
public:
    /// Constructor
    Rectangle();

    // Okay, but do not forget to call this!
    void Init(int screenWidth, int screenHeight);

    // Arguments here are a little redundant--do we need them?
    // (Perhaps if the screen resizes? Hmm!)
    void Update(int screenWidth, int screenHeight);

    // Okay, render our rectangle to a specific renderer!
    void Render(SDL_Renderer* renderer);

private:
    int x{100};
    int y{100};
    int w{100};
    int h{100};
    int speed{1};
    bool up{true};
    bool left{true};
};

#endif
