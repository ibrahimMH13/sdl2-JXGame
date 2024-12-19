#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <stdexcept>
#include <sstream>
#include "texture.h"
#include "LTexture.cpp"





SDL_Window* gWindow;

SDL_Renderer* gRenderer;

const int SCREEN_WIDTH = 1500;

const int SCREEN_HEIGHT = 1000;

LTexture texture;

void init(){

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
       throw std::runtime_error(std::string(SDL_GetError()));
    }

    if (TTF_Init() == -1)
    {
       throw std::runtime_error("error" + std::string(TTF_GetError()));
    }
    
    gWindow = SDL_CreateWindow("timer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (!gWindow)
    {
        throw std::runtime_error(std::string(SDL_GetError()));
    }
    
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

    texture = LTexture( gRenderer );
    
}

void close(){

    SDL_DestroyWindow(gWindow);

    SDL_DestroyRenderer(gRenderer);

    TTF_Quit();

    SDL_Quit();

    gWindow = nullptr;

    gRenderer = nullptr;

}

int main(){

    SDL_Event e;

    bool quit = false;
    
    Uint32 startTime = 0 ;

    std::stringstream timeText;

    try
    {
         init();
        
        if (
             !texture.setFontType("/System/Library/Fonts/SFNS.ttf",70)
        )
        {
            throw std::runtime_error("unable load font");
        }

        while (!quit)
        {
            
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

            SDL_RenderClear(gRenderer);

            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN)
                {
                   startTime = SDL_GetTicks();
                }
                
                
            }
            timeText.str( "" );
            timeText << "Milliseconds since start time " << SDL_GetTicks() - startTime; 
            texture.loadFromText(timeText.str().c_str(),{0xFF,0,0,0});

            texture.render(0, 0);

            SDL_RenderPresent(gRenderer);
            
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "\n@------------->"<< e.what() << "\n" << "here"<< '\n';
    }
    
    close();

    return 0;
}