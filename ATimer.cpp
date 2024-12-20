#include <iostream>
#include <SDL.h>
#include <string>
#include <iostream>
#include "texture.h"
#include "LTexture.cpp"
#include <stdexcept>
#include <sstream>
#include "timer.h"
#include "AdvanceTimer.cpp"

const int WEIGHT_SCREEN = 700;

const int HEIGHT_SCREEN = 700;

SDL_Window* gWindow;

SDL_Renderer* gRenderer;

LTexture texture;

void init(){

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
       throw std::runtime_error(std::string(SDL_GetError()));
    }
    
    gWindow = SDL_CreateWindow("Advance timer",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WEIGHT_SCREEN, HEIGHT_SCREEN , SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (!gWindow)
    {
        throw std::runtime_error(std::string(SDL_GetError()));
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

    if (!gRenderer)
    {
         throw std::runtime_error(std::string(SDL_GetError()));
    }

    texture = LTexture( gRenderer );
        
}

bool loadMedia(){

    return 0 ;
}

void close(){

    SDL_DestroyRenderer( gRenderer );

    SDL_DestroyWindow( gWindow );

    gRenderer = nullptr;

    gWindow = nullptr;

    SDL_Quit();
    
}

int main(){

    SDL_Event e;

    bool quit = false;

    SDL_Color textColor = { 0, 0, 0, 255 };

    AdvanceTimer timer;

    std::stringstream timeText;

    while (!quit)
    {
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        
        SDL_RenderClear(gRenderer);

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            
        }

        SDL_RenderPresent(gRenderer);
        
    }
    
    return 0;
};