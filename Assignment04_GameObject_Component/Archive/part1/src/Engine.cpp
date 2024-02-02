#include "Engine.hpp"
#include "Sprite.hpp"
#include "TileMap.hpp"
// I recommend a map for filling in the resource manager
#include <map>
#include <string>
#include <memory>
#include <iterator>

// Try toggling this number!
#define CHARACTERS 1

// Global array to create our characters
Sprite characters[CHARACTERS];

// Create a TileMap
TileMap* myTileMap;

// Initialization function
// Returns a true or false value based on successful completion of setup.
// Takes in dimensions of window.
Engine::Engine(){
}


// Proper shutdown and destroy initialized objects
Engine::~Engine(){
}

// Return Input
void Engine::Input(bool *quit){
    // Event handler that handles various events in SDL
    // that are related to input and output
    SDL_Event e;
    // Enable text input
    SDL_StartTextInput();
      //Handle events on queue
      while(SDL_PollEvent( &e ) != 0){
        // User posts an event to quit
        // An example is hitting the "x" in the corner of the window.
        if(e.type == SDL_QUIT){
          *quit = true;
        }
      }
}

// Update SDL
void Engine::Update()
{
    static int frame =0 ;
    
    // Increment the frame that
    // the sprite is playing
    frame++;
    if(frame>6){
        frame=0;
    }
    
    // iterate through each of our characters
    for(int i =0; i < CHARACTERS; i++){
        characters[i].Update(20,20, frame);
    }
}


// Render
// The render function gets called once per loop
void Engine::Render(){
    // Set the color of the empty framebuffer
    mRenderer->SetRenderDrawColor(110, 130,170,0xFF);
    // Clear the screen to the color of the empty framebuffer
    mRenderer->RenderClear();

    // NOTE: We have to dynamic_cast here, because we do not exactly know the type
    //       of the renderer that is going to 'render' our character.
    //       Polymorphism is being used for our renderer, and we need to thus
    //       determine using dynamic_cast if we can make a successful cast to find
    //       a matching member function that can retrieve a 'renderer' suitable.
    // NOTE: The very fact that I am storing an SDL_Renderer* below completely 
    //       defeats the purpose of using the dynamic_cast. 
    //       The whole point of the dynamic_cast is so that at run-time we can retrieve a
    //       renderer to draw our characters. 
    //       That said, it's just more readable for you to see the dynamic cast here.
    // NOTE: If dynamic_cast fails, you can check at run-time and handle through either an
    //       assertion or exception the behavior.
    SDL_Renderer* renderer = dynamic_cast<SDLGraphicsEngineRenderer*>(mRenderer)->GetRenderer();

    // Render each of the character(s)
    for(int i =0; i < CHARACTERS; i++){
        characters[i].Render(renderer);
    }

    // Render the tile map
    myTileMap->Render(renderer);

    // Flip the buffer to render
    mRenderer->RenderPresent();
}



//Loops forever!
void Engine::MainGameLoop(){
    // Main loop flag
    // If this is quit = 'true' then the program terminates.
    bool quit = false;

    // While application is running
    while(!quit){
      // Get user input
      Input(&quit);
      // If you have time, implement your frame capping code here
      // Otherwise, this is a cheap hack for this lab.
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

void Engine::Start(){
    // Report which subsystems are being initialized
    if(mRenderer!=nullptr){
        std::cout << "Initializing Graphics Subsystem\n";
    }else{
        std::cout << "No Graphics Subsystem initialized\n";
    }

    // Move Sprite to initial position
    characters[0].SetPosition(128,508);
    // Load an image for our character
    SDL_Renderer* renderer  = dynamic_cast<SDLGraphicsEngineRenderer*>(mRenderer)->GetRenderer();
    characters[0].LoadImage("./images/sprite.bmp",renderer);

    // Setup our TileMap
    // This tile map is 20x11 in our game
    // It is using a 'reference' tilemap with 8x8 tiles
    // that are each 64x64 pixels.
    myTileMap = new TileMap("./images/Tiles1.bmp",8,8,64,64,20,11,renderer);
    // Generate a a simple tilemap
    myTileMap->GenerateSimpleMap();
    // Print out the map to the console
    // so we can see what was created.
    myTileMap->PrintMap();

}

void Engine::Shutdown(){
    // Shut down our Tile Systems
    if(nullptr!=mRenderer){
        delete mRenderer;
    } 

    // Destroy our tilemap
    if(nullptr!=myTileMap){
        delete myTileMap;
    }
}

void Engine::InitializeGraphicsSubSystem(){
    // Setup our Renderer
    mRenderer = new SDLGraphicsEngineRenderer(1280,720);
    if(nullptr == mRenderer){
        exit(1); // Terminate program if renderer 
                 // cannot be created.
                 // (Optional) TODO:   Could put an error 
                 //                    messeage, or try to 
                 //                    reinitialize the engine 
                 //                    with a different render
    }
}
