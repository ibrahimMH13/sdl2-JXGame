#include <iostream>
#include <SDL.h>
#include <string>
#include <iostream>
#include "texture.h"
#include "LTexture.cpp"
#include <stdexcept>


SDL_Window* gWindow;

SDL_Renderer* gRenederer;

const int WINDOW_HIEGHT = 700;
const int WINDOW_WEIGHT = 500;

bool init(){

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        
        std::runtime_error("unable to init SDL2, SDL# " + std::string(SDL_GetError()));
    
    }

    gWindow = SDL_CreateWindow("Clip Renderer",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WINDOW_WEIGHT,WINDOW_HIEGHT,SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    
    if(gWindow == nullptr){

        std::runtime_error("Unable to create Window, SDL#" + std::string(SDL_GetError()));

    }

    gRenederer = SDL_CreateRenderer(gWindow,-1, SDL_RENDERER_ACCELERATED);

    if (gRenederer == nullptr)
    {
        std::runtime_error("Unable to create Renderer, SDL#" + std::string(SDL_GetError()));
    }
    
    return true;
}

bool close(){

    SDL_DestroyWindow(gWindow);

    SDL_DestroyRenderer(gRenederer);
    
    gWindow = nullptr;
    
    gRenederer = nullptr;
    
    SDL_Quit();

    return true;
}

int main(){

    SDL_Event e;
    
  
    bool quite = false;
    
    try{
         init();
        
        LTexture texture(gRenederer);

        while (!quite)
        {
            SDL_SetRenderDrawColor(gRenederer,0xFF, 0xFF, 0xFF, 0xFF);
           
            SDL_RenderClear(gRenederer);

           while (SDL_PollEvent(&e) != 0)
           {
              if(e.type == SDL_QUIT){

                quite = false;
              }

           }

            SDL_Rect gSpriteClips[4];

        //Set top left sprite
        gSpriteClips[ 0 ].x =   0;
        gSpriteClips[ 0 ].y =   0;
        gSpriteClips[ 0 ].w = 100;
        gSpriteClips[ 0 ].h = 100;

        //Set top right sprite
        gSpriteClips[ 1 ].x = 100;
        gSpriteClips[ 1 ].y =   0;
        gSpriteClips[ 1 ].w = 100;
        gSpriteClips[ 1 ].h = 100;
        
        //Set bottom left sprite
        gSpriteClips[ 2 ].x =   0;
        gSpriteClips[ 2 ].y = 100;
        gSpriteClips[ 2 ].w = 100;
        gSpriteClips[ 2 ].h = 100;

        //Set bottom right sprite
        gSpriteClips[ 3 ].x = 100;
        gSpriteClips[ 3 ].y = 100;
        gSpriteClips[ 3 ].w = 100;
        gSpriteClips[ 3 ].h = 100;

            texture.loadFromFile("dots.png");
            
            texture.render(0, 0, &gSpriteClips[0]);
            texture.render(WINDOW_WEIGHT - gSpriteClips[1].w , 0, &gSpriteClips[1]);
            texture.render(0 , WINDOW_HIEGHT - gSpriteClips[3].h, &gSpriteClips[3]);
            texture.render(WINDOW_WEIGHT - gSpriteClips[2].w , WINDOW_HIEGHT - gSpriteClips[2].h, &gSpriteClips[2]);
            SDL_RenderPresent(gRenederer);

        }
        
       

    }catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
      
    }
      close();
    return 0;
}