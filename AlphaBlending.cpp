#include <iostream>
#include <SDL.h>
#include <string>
#include <iostream>
#include "texture.h"
#include "LTexture.cpp"
#include <stdexcept>


SDL_Window* gWindow;

SDL_Renderer* gRenderer;

const int WIDTH_SCREEN = 640;

const int HEIGHT_SCREEN = 450;


void init(){

    if(SDL_Init(SDL_INIT_VIDEO) < 0){

        throw std::runtime_error("Unable to init: " + std::string(SDL_GetError()));
    
    }

    gWindow = SDL_CreateWindow("Alpha Blending",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WIDTH_SCREEN, HEIGHT_SCREEN, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (gWindow == nullptr)
    {
        throw std::runtime_error("Unable to create window: " + std::string(SDL_GetError()));
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

    if (gRenderer == nullptr)
    {
        throw std::runtime_error("Unable to create renderer: " + std::string(SDL_GetError()));
    }
    
}

void close(){

    SDL_DestroyWindow(gWindow);

    SDL_DestroyRenderer(gRenderer);

    gWindow = nullptr;

    gRenderer = nullptr;

    SDL_Quit();

}
int main(){

    SDL_Event e;

    bool quit = false;

    Uint8 a = 255;
    
    try
    {
        init();
        
        LTexture texture(gRenderer);

        LTexture gBackgroundTexture(gRenderer);

        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        
        SDL_RenderClear( gRenderer );

        while (!quit)
        {
                     //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    //Handle key presses
                    else if( e.type == SDL_KEYDOWN )
                    {
                        //Increase alpha on w
                        if( e.key.keysym.sym == SDLK_w )
                        {
                            //Cap if over 255
                            if( a + 32 > 255 )
                            {
                                a = 255;
                            }
                            //Increment otherwise
                            else
                            {
                                a += 32;
                            }
                        }
                        //Decrease alpha on s
                        else if( e.key.keysym.sym == SDLK_s )
                        {
                            //Cap if below 0
                            if( a - 32 < 0 )
                            {
                                a = 0;
                            }
                            //Decrement otherwise
                            else
                            {
                                a -= 32;
                            }
                        }
                    }
                }
            gBackgroundTexture.loadFromFile("fadein.png");

            gBackgroundTexture.render(0,0);
            
            texture.loadFromFile("fadeout.png");
            
            texture.setAlpa(a);

            texture.render(0,0);


            SDL_RenderPresent(gRenderer);
        }
                
        close();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}