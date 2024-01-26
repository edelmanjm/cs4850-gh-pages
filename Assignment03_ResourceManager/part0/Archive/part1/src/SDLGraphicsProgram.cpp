#include "SDLGraphicsProgram.hpp"
#include "ResourceManager.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

// Initialization function
// Returns a true or false value based on successful completion of setup.
// Takes in dimensions of window.
SDLGraphicsProgram::SDLGraphicsProgram(int w, int h):mScreenWidth(w),mScreenHeight(h){

    // Initialize SDL
    if(SDL_Init(SDL_INIT_EVERYTHING)< 0){
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
        exit(1);
    }

    //Create window
    mWindow = SDL_CreateWindow( "Lab", 100, 100, mScreenWidth, mScreenHeight, SDL_WINDOW_SHOWN );

    // Check if Window did not create.
    if( nullptr == mWindow){
        std::cerr << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
        exit(1);
    }

    //Create a Renderer to draw on
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
    // Check if Renderer did not create.
    if( nullptr == mRenderer ){
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << "\n";
        exit(1);
    }

    // SDL Setup successfully
    std::cout << "No SDL errors Detected in during init\n\n";
}



// Proper shutdown and destroy initialized objects
SDLGraphicsProgram::~SDLGraphicsProgram(){
    // Destroy Renderer
    SDL_DestroyRenderer(mRenderer);
    mRenderer   = nullptr;
    //Destroy window
    SDL_DestroyWindow( mWindow );
    // Point mWindow to NULL to ensure it points to nothing.
    // even in the instance that destroying the window fails
    mWindow     = nullptr;
    //Quit SDL subsystems
    SDL_Quit();
}



// Update
void SDLGraphicsProgram::Update()
{
    static int frame =0 ;
    frame++;
    if(frame>6){frame=0;}
    // Nothing yet!
    for(int i =0; i < mSprites.size(); i++){
        mSprites[i].Update(20,20, frame);
    }
}


// Render
// The render function gets called once per loop
void SDLGraphicsProgram::Render(){

    SDL_SetRenderDrawColor(mRenderer, 0x22,0x22,0x22,0xFF);
    SDL_RenderClear(mRenderer);  
   
    // Iterate through all of our sprites
    for(int i =0; i < mSprites.size(); i++){
        mSprites[i].Render(GetSDLRenderer());
    }

    SDL_RenderPresent(mRenderer);
}



//Loops forever!
void SDLGraphicsProgram::Loop(){
    // Call startup routine
    StartUp();

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

      // If you have time, implement your frame capping code here
      // Otherwise, this is a cheap hack to slow down the main game loop
      SDL_Delay(250);

      // Update our scene
      Update();
      // Render using OpenGL
      Render();
      //Update screen of our specified window
    }

    //Disable text input
    SDL_StopTextInput();
}

// Get Pointer to a specific window that we have created 
SDL_Window* SDLGraphicsProgram::GetSDLWindow(){
  return mWindow;
}

// Get Pointer to a specific SDLRenderer
SDL_Renderer* SDLGraphicsProgram::GetSDLRenderer(){
  return mRenderer;
}

// Startup Routine for our Graphics Application
void SDLGraphicsProgram::StartUp(){
    // Initialize random number generation.
    srand(time(nullptr));
    // Setup our characters
    // Remember, this can only be done after SDL has been
    // successfully initialized!
    // Here I am just building a little grid of characters
    unsigned int sum = 0;
    unsigned int yColumn = 0;
    constexpr int offset = 128;
    for(int i=0; i < 50; ++i){
        sum += offset;
        if (sum > mScreenWidth){
            yColumn+=offset;
            sum =0;
        }
        // This is functionally equivalent 
        // to mSprites.push_backpush_back(Sprite(..args));
        // The difference is that we can construct the object in place.
        // Note also that the move constructor can be called if we otherwise implement it.
        //
        mSprites.emplace_back(GetSDLRenderer(),sum,yColumn,"./../../common/sprites/sprite.bmp");
    }
}
