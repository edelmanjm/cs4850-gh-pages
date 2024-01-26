#ifndef SPRITE_HPP
#define SPRITE_HPP

#if defined(LINUX) || defined(MINGW)
    #include <SDL2/SDL.h>
#else // This works for Mac
    #include <SDL.h>
#endif

#include <string>

class Sprite{
public:
    // Construtor -- Create a new Sprite
	Sprite(SDL_Renderer* renderer, int x, int y, std::string image_filename);
    // Destructor
    ~Sprite();
    // Copy Constructor
    Sprite(const Sprite& rhs);
    // Move Constructor
    Sprite(Sprite&& rhs) = default;
    // Update the Sprite
	void Update(int x, int y, int frame);
    // Draw the Sprite
	void Render(SDL_Renderer* renderer);

private:
	int             mXPosition;
    int             mYPosition;
	unsigned int    mCurrentFrame{0};
	unsigned int    mLastFrame{7};
	SDL_Texture*    mTexture;
	SDL_Rect        mSrc;
	SDL_Rect        mDest;
};

#endif
