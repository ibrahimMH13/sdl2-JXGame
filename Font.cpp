#include <iostream>
#include <SDL.h>
#include <string>
#include <iostream>
#include "texture.h"
#include "LTexture.cpp"
#include <stdexcept>




const int WEIGHT_SCREEN = 700;

const int HEIGHT_SCREEN = 700;

SDL_Window* gWindow;

SDL_Renderer* gRenderer;

LTexture texture;


void init(){

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
       throw std::runtime_error("error" + std::string(SDL_GetError()));
    }

    if (TTF_Init() == -1)
    {
       throw std::runtime_error("error" + std::string(TTF_GetError()));
    }


    gWindow = SDL_CreateWindow("font",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WEIGHT_SCREEN,HEIGHT_SCREEN, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (!gWindow)
    {
        throw std::runtime_error("error" + std::string(SDL_GetError()));
    }

    gRenderer = SDL_CreateRenderer(gWindow,-1, SDL_RENDERER_ACCELERATED);

    if (!gRenderer)
    {
        throw std::runtime_error("error" + std::string(SDL_GetError()));
    }

    texture = LTexture(gRenderer);

}

void close(){

    SDL_DestroyRenderer(gRenderer);

    SDL_DestroyWindow(gWindow);

    SDL_Quit();

    TTF_Quit();

    gWindow = nullptr;

    gRenderer = nullptr;
}

int main(){

    SDL_Event e;

    bool quit = false;

    try
    {
        init();

        if (
                !texture.setFontType("/System/Library/Fonts/SFNS.ttf",70)->loadFromText("IBRAHIM I. I. MUSABEH",{0xFF,0,0,0})
            )
            {
              throw std::runtime_error("font issue" + std::string(TTF_GetError()));
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
                }
                
            }
            
            texture.render((WEIGHT_SCREEN - texture.getWidth()) / 2, (HEIGHT_SCREEN - texture.getHeight()) / 2);

            SDL_RenderPresent(gRenderer);
        }
        
    }
    catch(const std::exception& e)
    {
        std::cerr<< "---------->" << e.what() << '\n';
    }
    
    close();

    return 0;
}
