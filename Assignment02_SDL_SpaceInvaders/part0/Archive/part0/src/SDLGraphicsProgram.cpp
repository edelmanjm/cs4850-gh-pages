#include "SDLGraphicsProgram.hpp"
#include "Rectangle.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <time.h>       /* time */


// Initialization function
// Returns a true or false value based on successful completion of setup.
// Takes in dimensions of window.
SDLGraphicsProgram::SDLGraphicsProgram(int w, int h):mScreenWidth(w),mScreenHeight(h){
  // Initialize random number generation.
   srand(time(NULL));
    // Setup blocks
    mRectangles = new Rectangle[mBlocks];
    for(int i=0; i < mBlocks; ++i){
        mRectangles[i].Init(mScreenWidth,mScreenHeight);
    }


  // Initialization flag
    bool success = true;
  // String to hold any errors that occur.
  std::stringstream errorStream;
  // The window we'll be rendering to
  mWindow = NULL;
  // Render flag

	// Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO)< 0){
		errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
		success = false;
	}
	else{

		//Create window
		mWindow = SDL_CreateWindow( "Lab",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                mScreenWidth,
                                mScreenHeight,
                                SDL_WINDOW_SHOWN );

        // Check if Window did not create.
        if( mWindow == NULL ){
			errorStream << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
			success = false;
		}

		//Create a Renderer to draw on
        mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
        // Check if Renderer did not create.
        if( mRenderer == NULL ){
			errorStream << "Renderer could not be created! SDL Error: " << SDL_GetError() << "\n";
			success = false;
		}
        
  }

  // If initialization did not work, then print out a list of errors in the constructor.
  if(!success){
    errorStream << "Failed to initialize!\n";
    std::string errors=errorStream.str();
    std::cout << errors << "\n";
  }else{
    std::cout << "No SDL, or OpenGL, errors Detected\n\n";
  }
}




// Proper shutdown and destroy initialized objects
SDLGraphicsProgram::~SDLGraphicsProgram(){
    if(nullptr != mRectangles){
        delete[] mRectangles;
    }

    // Destroy Renderer
    SDL_DestroyRenderer(mRenderer);
	//Destroy window
	SDL_DestroyWindow( mWindow );
    // Point mWindow to NULL to ensure it points to nothing.
	mRenderer = NULL;
    mWindow = NULL;
	//Quit SDL subsystems
	SDL_Quit();
}



// Update OpenGL
void SDLGraphicsProgram::Update()
{
	// Nothing yet!
    SDL_SetRenderDrawColor(mRenderer, 0x22,0x22,0x22,0xFF);
    SDL_RenderClear(mRenderer);  
    for(int i =0; i < mBlocks; i++){
        mRectangles[i].Update(mScreenWidth,mScreenHeight);
    }
}


// Render
// The render function gets called once per loop
void SDLGraphicsProgram::Render(){

    for(int i =0; i < mBlocks; i++){
        mRectangles[i].Render(GetSDLRenderer());
    }

    SDL_RenderPresent(mRenderer);
}



//Loops forever!
void SDLGraphicsProgram::Loop(){

    // Main loop flag
    // If this is quit = 'true' then the program terminates.
    bool quit = false;
    // Event handler that handles various events in SDL
    // that are related to input and output
    SDL_Event e;
    // Enable text input
    SDL_StartTextInput();
    // While application is running
    while(!quit){
      //Handle events on queue
      while(SDL_PollEvent( &e ) != 0){
        // User posts an event to quit
        // An example is hitting the "x" in the corner of the window.
        if(e.type == SDL_QUIT){
          quit = true;
        }		
      }
	  // Update our scene
	  Update();

      SDL_Delay(16);
      // Render
      Render();
      //Update screen of our specified window
      // SDL_GL_SwapWindow(getSDLWindow());
    }

    //Disable text input
    SDL_StopTextInput();
}

// Get Pointer to Window
SDL_Window* SDLGraphicsProgram::GetSDLWindow(){
  return mWindow;
}

// Get Pointer to Renderer
SDL_Renderer* SDLGraphicsProgram::GetSDLRenderer(){
  return mRenderer;
}
