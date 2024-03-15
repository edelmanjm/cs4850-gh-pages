#ifndef SDL_LIBRARY_H
#define SDL_LIBRARY_H
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
#else // This works for Mac
    #include <SDL.h>
#endif


// Include library that allows embedding of pybind
// into the engine
#include <pybind11/embed.h>
#include <string>
#include <iostream>
namespace py = pybind11; // shorten what we need to type

class SDL{
public:
	SDL(){
		if(SDL_Init(SDL_INIT_VIDEO)< 0){
			// ... error handling here
			std::cerr << "cannot initialize SDL\n";
		}
	}

	~SDL(){
		SDL_Quit();
	}
};

class SDLWindow{
public:
	SDLWindow(const char* title, int x, int y, int w, int h ){
    	window = SDL_CreateWindow( title, x, y, w, h, SDL_WINDOW_SHOWN );
		if(nullptr == window){
			std::cerr << "window cannot be created\n";
		}
	}

	~SDLWindow(){
		SDL_DestroyWindow(window);
	}
	private:
	SDL_Window* window{nullptr};	

};

PYBIND11_MODULE(library, m){
	m.doc() = "SDL abstraction example"; // Optional docstring
	// List of SDL functions that are called

	// Class for creating an SDL window
	py::class_<SDL>(m, "SDL") // Our class 
		.def(py::init<>());    // Member functions starting with constructor

	py::class_<SDLWindow>(m, "SDLWindow")
		.def(py::init<const char*,int,int,int,int>(),
			 py::arg("title"),py::arg("x"),py::arg("y"),py::arg("w"),py::arg("h"));
}


#endif
