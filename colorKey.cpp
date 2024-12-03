#include <SDL.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "texture.h"

SDL_Window* gWindow = nullptr;

SDL_Texture* gFooTexture;

SDL_Texture* gBackgroundTexture;

SDL_Renderer* gRenderer;

int HIEGHT_WINDOW = 700;

int WIDETH_WINDOW = 500;

bool quit = false;


class LTexture;

bool init(int argc,char* argv[]){

    if(SDL_Init(SDL_INIT_VIDEO)< 0){
        std::cerr << "unable to init sdl" << SDL_GetError();
        return false;
    }

    gWindow = SDL_CreateWindow("ColorKey tutoral",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDETH_WINDOW,HIEGHT_WINDOW,SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
   
    if (gWindow == nullptr)
    {
       std::cerr << "unable to create window" << SDL_GetError();
       return false;
    }
    
    gRenderer = SDL_CreateRenderer(gWindow,-1, SDL_RENDERER_ACCELERATED);

    if (gRenderer == nullptr)
    {
        std::cerr << "unable to create render" << SDL_GetError();
       return false;
    }
    
    return true;
}

int main(){

    SDL_Event e;
    if (!init())
    {
        std::cerr << "something went wrong";
        return -1;
    }
    
    while (!quit)
    {
        // background white
        SDL_SetRenderDrawColor(gRenderer,0xFF, 0xFF, 0xFF, 0xFF);
        // clear bg
        SDL_RenderClear(gRenderer);

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
              quit = true;
            }
           
        }

        LTexture LTexture(gRenderer);

        LTexture.loadFromFile("press.bmp");

        gBackgroundTexture = LTexture.getTexture();
    
       SDL_RenderPresent(gRenderer);
        
    }
    

    return 0;
}