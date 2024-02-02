#include "Sprite.hpp"

Sprite::Sprite(){
}

Sprite::~Sprite(){
// TODO: Make sure spritesheet and mTexture are destroyed
// but is this the right place?
    SDL_FreeSurface(mSpriteSheet);
    mSpriteSheet = nullptr;
    SDL_DestroyTexture(mTexture);
}

// Set the sprite position
void Sprite::SetPosition(int x, int y){
    mPosition.x = x;
    mPosition.y = y;
}

void Sprite::Update(int x, int y, int frame){
    // The part of the image that we want to render
    mCurrentFrame = frame;
    if(mCurrentFrame>6){
        mCurrentFrame=0;
    }

    // Here I am selecting which frame I want to draw
    // from our sprite sheet. Think of this as just
    // using a mouse to draw a rectangle around the
    // sprite that we want to draw.
    mSrc.x = mCurrentFrame*75;
    mSrc.y = 0;
    mSrc.w = 75;
    mSrc.h = 87;

    // Where we want the rectangle to be rendered at.
    // This is an actual 'quad' that will draw our
    // source image on top of.	
    mDest.x = mPosition.x;
    mDest.y = mPosition.y;
    mDest.w = 128;
    mDest.h = 128;
}

void Sprite::Render(SDL_Renderer* ren){
    SDL_RenderCopy(ren, mTexture, &mSrc, &mDest);
}


void Sprite::LoadImage(std::string filePath, SDL_Renderer* ren){
    mSpriteSheet = SDL_LoadBMP(filePath.c_str());
    if(nullptr == mSpriteSheet){
           SDL_Log("Failed to allocate surface");
    }else{
        SDL_Log("Allocated a bunch of memory to create identical game character");
        // Create a texture from our surface
        // Textures run faster and take advantage 
        // of hardware acceleration
        mTexture = SDL_CreateTextureFromSurface(ren, mSpriteSheet);
    }
}
