#include <iostream>
#include <SDL.h>
#include <string>
#include <iostream>
#include "texture.h"
#include "LTexture.cpp"
#include <stdexcept>

SDL_Window* gWindow;

SDL_Renderer* gRenderer;

int WINDOW_WEGIHT = 750;

int WINDOW_HEIGHT = 750;

int init(){

    if (SDL_Init(SDL_INIT_VIDEO) <0)
    {
        
        std::runtime_error("Unable init to video ,SDL ERROR " + std::string(SDL_GetError()));

    }

    gWindow = SDL_CreateWindow("Color Modulation",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_CENTERED,WINDOW_WEGIHT,WINDOW_HEIGHT,SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);        

    if(gWindow == nullptr){

        std::runtime_error("Unable create window ,SDL ERROR " + std::string(SDL_GetError()));

    }
    
    gRenderer = SDL_CreateRenderer(gWindow,-1, SDL_RENDERER_ACCELERATED);

    if (gRenderer == nullptr)
    {

         std::runtime_error("Unable Renderer ,SDL ERROR " + std::string(SDL_GetError()));

    }

    return true;
    
}

void close(){
    
    SDL_DestroyWindow(gWindow);

    SDL_DestroyRenderer(gRenderer);

    gRenderer = nullptr;

    gWindow = nullptr;

}
int main(){

        SDL_Event e;

        bool quit = false;
        
        Uint8 r = 255;
        Uint8 g = 255;
        Uint8 b = 255;

   try
   {
        init();

        LTexture texture(gRenderer);
        texture.loadFromFile("colors.png");
        while (!quit)
        {
            SDL_SetRenderDrawColor(gRenderer,0xFF, 0xFF, 0xFF, 0xFF);
            
            SDL_RenderClear(gRenderer);

            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                
                }else if(e.type == SDL_KEYDOWN){

                    switch (e.key.keysym.sym)
                    {
                    
                    case SDLK_q:

                        r+= 43;
                      
                        break;
                    
                    case SDLK_w:
                      
                        g+=32;
                      
                        break;

                    case SDLK_e:

                        b +=32;
                    
                    case SDLK_s:

                        g -=32;
                        
                        break;

                    case SDLK_d:

                        b -= 32;

                        break;
                    default:
                        break;
                    }
                }
                
            }

           
            
            texture.setColor(r, g, b);
            
            texture.render(50,150);
            
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