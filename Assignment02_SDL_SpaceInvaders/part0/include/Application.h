// Application.hpp
#pragma once

#include <SDL3/SDL.h>
#include <cstdlib>
#include <vector>
#include <memory>

struct Sprite{
    Sprite(){
        
    }

	void CreateSprite(SDL_Renderer* renderer, const char* filepath){
        SDL_Surface* pixels = SDL_LoadBMP(filepath);
        SDL_SetSurfaceColorKey(pixels,SDL_TRUE,SDL_MapRGB(pixels->format,0xFF,0,0xFF));

        mTexture = SDL_CreateTextureFromSurface(renderer,pixels);
        if(nullptr==mTexture){
            SDL_Log("Could not load texture from surface");
        }
        
        SDL_DestroySurface(pixels);
	}

    ~Sprite(){
//        SDL_DestroyTexture(mTexture);
//        TODO: We'll want a resource manager to handle this.
    }

	void Update(float deltaTime){
	}
	void Render(SDL_Renderer* renderer){
        if(nullptr==mTexture){
		    SDL_RenderRect(renderer, &mRectangle);
        }else{
            SDL_RenderTexture(renderer,mTexture,nullptr,&mRectangle);
        }
	}

    void SetW(float w){
        mRectangle.w = w;
    }

    void SetX(float x){
        mRectangle.x = x;
    }
    void SetY(float y){
        mRectangle.y = y;
    }

    float GetX() const{
        return mRectangle.x;
    }
    float GetY() const{
        return mRectangle.y;
    }

    void Move(float x, float y){
        mRectangle.x = x;
        mRectangle.y = y;
    }

    SDL_FRect GetRectangle() const{
        return mRectangle;
    }

	private:
		SDL_FRect mRectangle{20.0f,20.0f,32.0f,32.0f};
        SDL_Texture* mTexture;
};


struct GameEntity{

    GameEntity(Sprite sprite){
        mSprite = sprite;
    }

    virtual ~GameEntity(){
    }

    virtual void Input(float deltaTime){
    }

    virtual void Update(float deltaTime){
    }

    virtual void Render(SDL_Renderer* renderer){
    }

    void SetRenderable(bool value){
        mRenderable = value;
    }

    bool IsRenderable() const{
        return mRenderable;
    }

    bool Intersects(std::shared_ptr<GameEntity> e){
        SDL_FRect source = e->mSprite.GetRectangle();
        SDL_FRect us     = mSprite.GetRectangle();
        SDL_FRect result;
        return SDL_GetRectIntersectionFloat(&source,&us,&result);
    }

    protected:
        Sprite mSprite;
        bool mRenderable{true};
};

struct Projectile : public GameEntity{

    Projectile(Sprite sprite) : GameEntity(sprite){
        timeSinceLastLaunch = SDL_GetTicks();
        mRenderable=false;
    }

    void Launch(float x, float y, bool yDirectionIsUp, int minlaunchtime=3000){
       if(SDL_GetTicks() - timeSinceLastLaunch > minlaunchtime){
            timeSinceLastLaunch = SDL_GetTicks();
            mIsFiring=true;        
            mYDirectionUp = yDirectionIsUp;
            mSprite.Move(x,y);
       }
    }

    void Update(float deltaTime) override{
        if(mIsFiring){
            mRenderable = true;
            if(true == mYDirectionUp){
                mSprite.SetY(mSprite.GetY() - mSpeed * deltaTime);
            }else{
                mSprite.SetY(mSprite.GetY() + mSpeed * deltaTime);
            }
        }else{
            mRenderable=false;
        }

        if(mSprite.GetY() < 0.0f || mSpeed > 480.0f){
            mIsFiring=false;
        }
    }

    void Render(SDL_Renderer* renderer) override{
        if(mRenderable){
            mSprite.Render(renderer);
        }else{
            // Do nothing;
        }
    }

    private:
        float mSpeed{200.0f};
        bool mIsFiring{false};
        bool mYDirectionUp{true};
        Uint64 timeSinceLastLaunch;
};

struct EnemyGameEntity : public GameEntity{

    EnemyGameEntity(SDL_Renderer* renderer, Sprite sprite) : GameEntity(sprite){
        Sprite sp;
        sp.CreateSprite(renderer,"../assets/rocket.bmp");
        sp.SetW(24.0f);
        mProjectile = std::make_shared<Projectile>(sp);

        // Set a random launch time for the enemies
        mMinLaunchTime += std::rand() % 10000;
    }

    virtual ~EnemyGameEntity(){
    }

    virtual void Input(float deltaTime) override{
    }

    virtual void Update(float deltaTime) override{
        mProjectile->Update(deltaTime);
		if(offset>80){
            xPositiveDirection=false;
		}
		if(offset<-80){
            xPositiveDirection=true;
		}

        if(xPositiveDirection){
            mSprite.SetX(mSprite.GetX() + mSpeed*deltaTime);
            offset += mSpeed * deltaTime;
        }else{
            mSprite.SetX(mSprite.GetX() - mSpeed*deltaTime);
            offset -= mSpeed * deltaTime;
        }

        if(mRenderable){
            mProjectile->Launch(mSprite.GetX(),mSprite.GetY(),false,mMinLaunchTime);
        }
    }

    virtual void Render(SDL_Renderer* renderer){
        if(mRenderable){
            mProjectile->Render(renderer);
            mSprite.Render(renderer);
        }else{
            // Do nothing;
        }
    }

    virtual std::shared_ptr<Projectile> GetProjectile() const{
        return mProjectile;
    }

    private:
        std::shared_ptr<Projectile> mProjectile;
		bool xPositiveDirection{true};
        float offset{0.0f};
        float mSpeed{100.0f};
        float mMinLaunchTime{5000.0f};
};


struct PlayerGameEntity : public GameEntity{

    PlayerGameEntity(SDL_Renderer* renderer, Sprite sprite) : GameEntity(sprite){

        Sprite sp;
        sp.CreateSprite(renderer,"../assets/rocket.bmp");
        sp.SetW(24.0f);
        mProjectile = std::make_shared<Projectile>(sp);
    }

    virtual ~PlayerGameEntity(){
    }

    virtual void Input(float deltaTime) override{
        const Uint8* state = SDL_GetKeyboardState(nullptr);
        if(state[SDL_SCANCODE_LEFT]){
            mSprite.SetX(mSprite.GetX() - mSpeed*deltaTime);
        }else if(state[SDL_SCANCODE_RIGHT]){
            mSprite.SetX(mSprite.GetX() + mSpeed*deltaTime);
        }

        if(state[SDL_SCANCODE_UP]){
            SDL_Log("Launching!");
            mProjectile->Launch(mSprite.GetX(),mSprite.GetY(),true);
        }
    }

    virtual void Update(float deltaTime) override{
        mProjectile->Update(deltaTime);
    }

    virtual void Render(SDL_Renderer* renderer){
        mProjectile->Render(renderer);
        mSprite.Render(renderer);
    }

    virtual std::shared_ptr<Projectile> GetProjectile() const{
        return mProjectile;
    }

    private:
        float mSpeed{150.0f};
        std::shared_ptr<Projectile> mProjectile;
};

struct Application{
    Application(int argc, char* argv[]){
        StartUp();
    }
    ~Application(){
        Shutdown();
    }

    void StartUp(){
        if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)!=0){
            SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        }
        // Create our window
        SDL_Window* mWindow = SDL_CreateWindow("An SDL3 Window",640,480,
                                                SDL_WINDOW_OPENGL);
        mRenderer = SDL_CreateRenderer(mWindow, NULL, SDL_RENDERER_ACCELERATED);
        if(nullptr == mRenderer){
            SDL_Log("Error creating renderer");
        }

        // Initialize all of the enemies
        int row=1;
        int column=1;
        for(int i=0; i<36; i++){
            Sprite sp;
            sp.CreateSprite(mRenderer,"../assets/enemy.bmp");

            if(i%12==0){
                ++row;
                column=0;
            }
            sp.Move(column*40+80,row*40);
            column++;
            std::unique_ptr<EnemyGameEntity> e = std::make_unique<EnemyGameEntity>(mRenderer,sp);
            enemies.push_back(std::move(e));
        }

        Sprite characterSprite;
        characterSprite.CreateSprite(mRenderer,"../assets/hero.bmp");
        characterSprite.Move(640/2 - (32/2),440);
        mainCharacter = std::make_unique<PlayerGameEntity>(mRenderer,characterSprite);
    }
    void Shutdown(){
        SDL_DestroyWindow(mWindow);
        SDL_Quit();
    }

    void Input(float deltaTime){
        SDL_Event event;
        // Processing input
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_EVENT_QUIT){
                SDL_Log("Program quit %li",event.quit.timestamp);
                mRun=false;
            }
            else if(event.type== SDL_EVENT_KEY_DOWN){
//                SDL_Log("Some key was pressed down");
//                SDL_Log("%u",event.key.keysym.sym);
//                if(event.key.keysym.sym == SDLK_0){
//                    SDL_Log("0 was pressed");
//                }
            }
        }

        // Handle SDL_GetKeyboardState after -- your SDL_PollEvent
        mainCharacter->Input(deltaTime);
    }

    void Update(float deltaTime){
        // Updating all of our enemies
        for(int i=0; i < enemies.size(); i++){
            enemies[i]->Update(deltaTime);

            bool enemyIsHit= enemies[i]->Intersects(mainCharacter->GetProjectile());

            bool GameOver = mainCharacter->Intersects(enemies[i]->GetProjectile());
            if(true==enemyIsHit && enemies[i]->IsRenderable()==true){
                enemies[i]->SetRenderable(false);
                mPoints += 10.0f;
                SDL_Log("Your score is %f",mPoints);
            }

            if(true==GameOver){
               SDL_Log("YOU LOOOOOOOOOSE!"); 
               SDL_Log("Your score is %f",mPoints);
               mRun = false;
            }
        }
        // Update our main character
        mainCharacter->Update(deltaTime);

        

    }

    void Render(){
		SDL_SetRenderDrawColor(mRenderer, 0, 64, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(mRenderer);

		SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        // Render our enemies
        for(int i=0; i < enemies.size(); i++){
            enemies[i]->Render(mRenderer);
        }
        // Render our main character
        mainCharacter->Render(mRenderer);

        SDL_RenderPresent(mRenderer);
    }

    void Loop(float targetFPS){
        // Our infinite game/application loop

        Uint64 lastTime, currentTime;

        // Record our 'starting time'
        lastTime = SDL_GetTicks();
        Uint64 framesElapsed=0;
        float deltaTime = 1.0f/targetFPS;
        while(mRun){
            Uint64 startOfFrame=SDL_GetTicks();
            // We want, input/update/render to take 16ms
            Input(deltaTime);
            Update(deltaTime);
            Render();
            Uint64 elapsedTime=SDL_GetTicks()-startOfFrame;
            framesElapsed++;

            // Time keeping code - for frames elapsed
            currentTime = SDL_GetTicks();
            // Insert a 'frame cap' so that our program
            // does not run too fast.
            if(elapsedTime < (1000/targetFPS)){
                Uint64 delay = (1000/targetFPS)-elapsedTime;
                SDL_Delay(delay);
//                SDL_Log("elaspedTime: %li",elapsedTime);
//                SDL_Log("delaying by: %li",delay);
            }
            // If 1 second passes,              enemies[i]->report how many frames
            // have been executed.
            if(currentTime > lastTime+1000){
                SDL_Log("1 second has elapsed");
                SDL_Log("%li",framesElapsed);
                deltaTime = 1.0f/framesElapsed;
                framesElapsed=0;
                lastTime=SDL_GetTicks();
            }

        }
    }

    private:
       // Enemy sprites
       std::vector<std::unique_ptr<EnemyGameEntity>> enemies;  
       // Main Character
       std::unique_ptr<PlayerGameEntity> mainCharacter;

       bool        mRun{true};
       float       mPoints{0.0f};
       SDL_Window* mWindow;
       SDL_Renderer* mRenderer;
};
