#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // This works for Mac
    #include <SDL.h>
#endif

// I recommend a map for filling in the resource manager
#include <unordered_map>
#include <string>

class ResourceManager{
public:
    // TODO: Make constructor private 
	ResourceManager();
    // Destructor
    // In theory, this is never called
	~ResourceManager();
    // TODO: Refactor as needed
    void LoadResource(std::string image_filename);
    // TODO: Refactor as needed
    SDL_Surface* GetResource(std::string image_filename);

private:
    SDL_Surface* mSpriteSheet;
};


#endif
