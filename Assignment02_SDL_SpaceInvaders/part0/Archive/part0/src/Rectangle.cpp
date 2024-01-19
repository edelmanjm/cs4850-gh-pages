#include "Rectangle.hpp"

// Just a cheap little class to give a visual effect that stresses the system.
// This should also be useful for helping you get started with your breakout code!
// Move this to its own .h and .cpp files for best practice!
Rectangle::Rectangle(){
    // Empty constructor! We have complete control!
}

// Okay, but do not forget to call this!
void Rectangle::Init(int screenWidth, int screenHeight){
    x = rand()%screenWidth;
    y = rand()%screenHeight;
    w = rand()%100;
    h = rand()%100;
    speed = rand()%2+1; 
}

// Arguments here are a little redundant--do we need them?
// (Perhaps if the screen resizes? Hmm!)
void Rectangle::Update(int screenWidth, int screenHeight){
    if(up){
        y+=speed;
        if(y>screenHeight){
            up = !up;
        }
    }

    if(!up){
        y-=speed;
        if(y<0){
            up = !up;
        }
    }
    if(left){
        x+=speed;
        if(x>screenWidth){
            left = !left;
        }
    }

    if(!left){
        x-=speed;
        if(x<0){
            left = !left;
        }
    }
}

// Okay, render our rectangles!
void Rectangle::Render(SDL_Renderer* renderer){
    SDL_Rect fillRect = {x,y,w,h};
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderDrawRect(renderer, &fillRect); 
}
