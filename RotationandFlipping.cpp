#include <iostream>
#include <SDL.h>
#include <string>
#include <iostream>
#include "texture.h"
#include "LTexture.cpp"
#include <stdexcept>


SDL_Window* gWindow;

SDL_Renderer* gReneder;

LTexture texture;

const int HEIGHT_WINDOW = 750;

const int WIEGHT_WINDOW = 700;

void init(){

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::runtime_error("unable " + std::string(SDL_GetError()));
    }

    gWindow = SDL_CreateWindow("Rotation and flipping",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WIEGHT_WINDOW,HEIGHT_WINDOW,SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    
    if (!gWindow)
    {
       std::runtime_error("unable Window" + std::string(SDL_GetError()));
    }
    
    gReneder = SDL_CreateRenderer(gWindow,-1, SDL_RENDERER_ACCELERATED);
    
    if (!gReneder)
    {
       std::runtime_error("unable Reneder" + std::string(SDL_GetError()));
    }

     texture = LTexture( gReneder);

}

void media(){

}

void close(){

    SDL_DestroyWindow(gWindow);

    SDL_DestroyRenderer(gReneder);  

    gWindow = nullptr;

    gReneder = nullptr;
    
    SDL_Quit();
}

int main(){


   SDL_Event e;

   bool quit = false;

   double degree = 0;

   SDL_RendererFlip filpType = SDL_FLIP_NONE;

   try
   {
   
   init();
   texture.loadFromFile("arrow.png");
    while (!quit)
    {
      SDL_SetRenderDrawColor(gReneder, 0xFF, 0xFF, 0xFF, 0xFF);
      SDL_RenderClear(gReneder);
       while (SDL_PollEvent(&e) != 0)
       {
            if (e.type == SDL_QUIT)
            {
               quit = true;
            }
            else if(e.type == SDL_KEYDOWN){
               
               switch (e.key.keysym.sym)
               {
               case SDLK_a:
                     degree -=60;
                     break;
               case SDLK_d:
                     degree += 60;
                     break;
               case SDLK_q:
                     filpType = SDL_FLIP_HORIZONTAL;
               case SDLK_w:
                     filpType = SDL_FLIP_NONE;
               case SDLK_e:
                     filpType = SDL_FLIP_VERTICAL;   
               default:
                  break;
               }
            }
            
       }
       
       texture.render((WIEGHT_WINDOW - texture.getWidth() )/ 2,
                      (HEIGHT_WINDOW - texture.getHeight()) / 2,
                        NULL,
                        degree,
                        NULL, 
                        filpType);
                        
       SDL_RenderPresent(gReneder);
    }

    close();

   }
   catch(const std::exception& e)
   {
      std::cerr <<"@------------------------------------>\n"<< e.what() << '\n';
   }
   

    return 0;
}