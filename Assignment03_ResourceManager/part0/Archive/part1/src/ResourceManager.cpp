// I recommend an unordered_map for filling in the resource manager
#include "ResourceManager.hpp"
#include <iterator>
#include <iostream>

ResourceManager::ResourceManager(){
}


ResourceManager::~ResourceManager(){
}

// TODO: YUCK! Fix this common resource consumption error.
//       You should use some data structure (e.g. a Map or unordered_map
//       to first search if this resource has been loaded, and then
//       only call SDL_LoadBMP if that resource does not previously exist.
void ResourceManager::LoadResource(std::string image_filename){
    std::cout << "New copy of " << image_filename << " has been loaded\n";
    mSpriteSheet = SDL_LoadBMP(image_filename.c_str());
}

SDL_Surface* ResourceManager::GetResource(std::string image_filename){
    std::cout << "Retrieved saved copy of " << image_filename << " from GetResource\n";
    return mSpriteSheet;
}


