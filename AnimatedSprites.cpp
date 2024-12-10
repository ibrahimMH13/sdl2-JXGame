#include <iostream>
#include <SDL.h>
#include <string>
#include <iostream>
#include "texture.h"
#include "LTexture.cpp"
#include <stdexcept>


SDL_Window* gWindow;

SDL_Renderer* gRenderer;

LTexture texture( gRenderer );

const int WEIGHT_SCREEN = 700;

const int HEIGHT_SCREEN = 700;


const int MAX_IFRAME = 4;

SDL_Rect gSpriteClips[4];

void init(){

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        
        std::runtime_error("Unable init " + std::string(SDL_GetError()));
    
    }

    gWindow = SDL_CreateWindow("Animation",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WEIGHT_SCREEN, HEIGHT_SCREEN, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (gWindow == nullptr)
    {
    
      std::runtime_error("Unable to create window,\n SDL" + std::string(SDL_GetError()));
    
    }

    gRenderer = SDL_CreateRenderer(gWindow,-1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (gRenderer == nullptr)
    {
        std::runtime_error("Unable to create renderer,\n SDL" + std::string(SDL_GetError()));
    }
    
        texture = LTexture(gRenderer);
        
}


void close(){

    SDL_DestroyWindow(gWindow);

    SDL_DestroyRenderer(gRenderer);

    SDL_Quit();

    gRenderer = nullptr;

    gWindow = nullptr;


}

bool loadMedia(){

    if(!texture.loadFromFile("mFoo.png")){

        return false;

    }else{

        gSpriteClips[0].x = 0;
        gSpriteClips[0].y = 0;
        gSpriteClips[0].w = 64;
        gSpriteClips[0].h = 205;

        gSpriteClips[1].x = 64;
        gSpriteClips[1].y = 0;
        gSpriteClips[1].w = 64;
        gSpriteClips[1].h = 205;

        gSpriteClips[2].x = 128;
        gSpriteClips[2].y = 0;
        gSpriteClips[2].w = 64;
        gSpriteClips[3].h = 205;

        gSpriteClips[3].x = 192;
        gSpriteClips[3].y = 0;
        gSpriteClips[3].w = 64;
        gSpriteClips[3].h = 205;


    }


    return true;

}

int main(){
    
    SDL_Event e;

    int iframe = 0;

    bool quit = false;

    try
    {
        
    init();
    
    loadMedia();
    
    while (!quit)
    {
        
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		
        SDL_RenderClear( gRenderer );

        SDL_Rect* currentClip = &gSpriteClips[ iframe / MAX_IFRAME ];

        texture.render(( WEIGHT_SCREEN - currentClip->w ) / 2,( HEIGHT_SCREEN - currentClip->h / 2 ), currentClip);

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            
        }

        ++iframe;

        if(iframe / 4 >= MAX_IFRAME){

            iframe = 0;
        }

        SDL_RenderPresent(gRenderer);

    }
    
     }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    close();
    return 0;
}