#include <iostream>
#include <SDL.h>
#include <string>
#include <iostream>
#include "texture.h"
#include "LTexture.cpp"
#include <stdexcept>


const int SCREEN_WIDTH = 640;

const int SCREEN_HEIGHT = 700;

SDL_Window* gWindow;

SDL_Renderer* gReneder;

LTexture gPressTexture;

LTexture gDownTexture;

LTexture gUpTexture;

LTexture gLeftTexture;

LTexture gRightTexture;

void init(){

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        throw std::runtime_error(std::string(SDL_GetError())); 
    }

    gWindow = SDL_CreateWindow("key state",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_CENTERED,SCREEN_HEIGHT, SCREEN_WIDTH, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    
    if(!gWindow)
    {
       throw std::runtime_error(std::string(SDL_GetError()));
    }

    gReneder = SDL_CreateRenderer(gWindow,-1, SDL_RENDERER_ACCELERATED);

    gPressTexture = LTexture( gReneder );

    gDownTexture = LTexture( gReneder );
    
    gUpTexture = LTexture( gReneder );
    
    gLeftTexture = LTexture( gReneder );
    
    gRightTexture = LTexture( gReneder );
    
}

bool loadMedia(){

    if (!gPressTexture.loadFromFile("press.png"))
    {
        throw std::runtime_error(std::string(SDL_GetError())); 
        return false;
    }

    if (!gRightTexture.loadFromFile("right.png"))
    {
        throw std::runtime_error(std::string(SDL_GetError())); 
        return false;
    }

    if (!gLeftTexture.loadFromFile("left.png"))
    {
        throw std::runtime_error(std::string(SDL_GetError())); 
        return false;
    }
    
    if (!gUpTexture.loadFromFile("up.png"))
    {
        throw std::runtime_error(std::string(SDL_GetError())); 
        return false;
    }

    if (!gDownTexture.loadFromFile("down.png"))
    {
        throw std::runtime_error(std::string(SDL_GetError())); 
        return false;
    }

    return true;
    
}

void close(){

    SDL_DestroyRenderer( gReneder );

    SDL_DestroyWindow( gWindow );
    
    gPressTexture.free();
    
    gUpTexture.free();
    
    gDownTexture.free();
    
    gLeftTexture.free();

    gRightTexture.free();

    SDL_Quit();
}

int main(){

    SDL_Event e;

    int quit = false;

    try
    {
        init();

        loadMedia();

        LTexture* currentTexture = nullptr;

        while (!quit)
        {
            SDL_SetRenderDrawColor(gReneder, 0xFF, 0xFF, 0xFF, 0xFF);
            
            SDL_RenderClear(gReneder);

            const Uint8* currentKeyState = SDL_GetKeyboardState(nullptr);

            while (SDL_PollEvent(&e) !=0)
            {
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }
                
            }

            if (currentKeyState [SDL_SCANCODE_UP])
            {
                currentTexture = &gUpTexture;
            }
            else if (currentKeyState[SDL_SCANCODE_DOWN])
            {
                currentTexture = &gDownTexture;
            }
            else if (currentKeyState[SDL_SCANCODE_LEFT])
            {
                currentTexture = &gLeftTexture;
            }
            else if (currentKeyState[SDL_SCANCODE_RIGHT])
            {
                currentTexture = &gRightTexture;
            }else{
                currentTexture = &gPressTexture;
            }
            
            currentTexture->render(0,0);

            SDL_RenderPresent( gReneder );
            
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    close();

    return 0;
}