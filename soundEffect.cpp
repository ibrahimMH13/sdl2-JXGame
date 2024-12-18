#include <iostream>
#include <SDL.h>
#include <string>
#include <iostream>
#include "texture.h"
#include "LTexture.cpp"
#include <stdexcept>
#include <SDL_mixer.h>


SDL_Window* gWindow;

SDL_Renderer* gRenderer;

const int SCREEN_WIDTH = 640;

const int SCREEN_HEIGHT = 700;

LTexture gTexture;
 
Mix_Music* gMusic;

Mix_Chunk* gStrach;

Mix_Chunk* gHigh;

Mix_Chunk* gMedium;

Mix_Chunk* gLow;


void init(){

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        throw std::runtime_error(std::string(SDL_GetError()));
    }
    
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
	{
		 throw std::runtime_error(std::string(SDL_GetError()));
    }

	gWindow = SDL_CreateWindow( "Sounds effect Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN );

    if (!gWindow)
    {
        throw std::runtime_error(std::string(SDL_GetError()));
    }
    

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
	{
		
        throw std::runtime_error(std::string(SDL_GetError()));
					
	}

   gTexture = LTexture ( gRenderer );
    
}

void close(){

    SDL_DestroyWindow(gWindow);

    SDL_DestroyRenderer(gRenderer);

    gRenderer = nullptr;

    gWindow = nullptr;

    Mix_FreeChunk(gStrach);

    Mix_FreeChunk(gHigh);
    
    Mix_FreeChunk(gLow);

    Mix_FreeChunk(gMedium);

    Mix_FreeMusic(gMusic);

    gStrach = nullptr;

    gHigh = nullptr;

    gMedium = nullptr;

    gLow = nullptr;

    gMusic = nullptr;

    Mix_Quit();

    SDL_Quit();
}

bool loadMedia(){

    if (!gTexture.loadFromFile("assets/image/prompt.png"))
    {
       throw std::runtime_error(std::string(SDL_GetError()));
        return false;
    }


    gMusic = Mix_LoadMUS("assets/audio/beat.wav");

    if (!gMusic)
    {
        std::runtime_error(std::string(Mix_GetError()));

        return false;
    }

    gStrach = Mix_LoadWAV("assets/audio/scratch.wav");

    if (!gStrach)
    {
        std::runtime_error(std::string(Mix_GetError()));
        return false;
    }

    gHigh = Mix_LoadWAV("assets/audio/high.wav");

    if (!gHigh)
    {
        std::runtime_error(std::string(Mix_GetError()));
        return false;
    }

     gMedium = Mix_LoadWAV("assets/audio/medium.wav");

    if (!gMedium)
    {
        std::runtime_error(std::string(Mix_GetError()));
        return false;
    }

    gLow = Mix_LoadWAV("assets/audio/low.wav");

    if (!gLow)
    {
        std::runtime_error(std::string(Mix_GetError()));
        return false;
    }
    
    return true;
}

int main(){

    SDL_Event e;

    bool quit = false;

    try
    {
        init();
        
        if (!loadMedia())
        {
            throw std::runtime_error(std::string(SDL_GetError()));
        }
        
        while (!quit)
        {

        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        
        SDL_RenderClear( gRenderer );

            while (SDL_PollEvent(&e) != 0)
            {
               if (e.type == SDL_QUIT)
               {
                 quit = true;
               }
               else if (e.type == SDL_KEYDOWN)
               {
                 switch (e.key.keysym.sym)
                 {
                 case SDLK_1:
                    Mix_PlayChannel( -1, gHigh, 0 );
                    break;
                case SDLK_2:
                    Mix_PlayChannel( -1, gMedium, 0 );
                    break;
                case SDLK_3:
                    Mix_PlayChannel( -1, gLow, 0 );
                    break;
                case SDLK_4:
                    Mix_PlayChannel( -1, gStrach, 0 );
                    break;
                case SDLK_9:
                if (Mix_PlayingMusic() == 0)
                {
                    Mix_PlayMusic(gMusic, -1);
                }else{
                
                    if (Mix_PausedMusic() == 1)
                    {
                        Mix_ResumeMusic();
                    }else{
                        Mix_PauseMusic();
                    }
                    
                }
                break;
                case SDLK_0:

                    Mix_HaltMusic();
                    break;
                 }
               }
               
            }

            gTexture.render(0,0);

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