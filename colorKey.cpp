#include <SDL.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "texture.h"
#include "LTexture.cpp"

SDL_Window* gWindow = nullptr;

SDL_Renderer* gRenderer;

const int HIEGHT_WINDOW = 640;

const int WIDETH_WINDOW = 480;

bool quit = false;


bool init(){

    if(SDL_Init(SDL_INIT_VIDEO)< 0){
        std::cerr << "unable to init sdl" << SDL_GetError();
        return false;
    }

    gWindow = SDL_CreateWindow("ColorKey tutoral",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDETH_WINDOW,HIEGHT_WINDOW,SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
   
    if (gWindow == nullptr)
    {

      std::cerr << "Unable to init SDL: " << SDL_GetError() << std::endl;

       return false;
    }
    
    gRenderer = SDL_CreateRenderer(gWindow,-1, SDL_RENDERER_ACCELERATED);

    if (gRenderer == nullptr)
    {

       std::cerr << "Unable to init SDL: " << SDL_GetError() << std::endl;

       return false;
    }
    
    return true;
}

void close(){

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    
    gRenderer = nullptr;
    gWindow = nullptr;

    IMG_Quit();
    SDL_Quit();

}

int main(int argc,char* argv[]){

    SDL_Event e;
    if (!init())
    {
       std::cerr << "Unable to init SDL: " << SDL_GetError() << std::endl;
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

        LTexture texture( gRenderer );
        
        texture.loadFromFile("background.png");
        texture.render(0,0);
        texture.free();

        texture.loadFromFile("foo.png");
        texture.render(240, 190);
        texture.free();
        
       SDL_RenderPresent(gRenderer);
        
    }
    
    close();
    return 0;
}