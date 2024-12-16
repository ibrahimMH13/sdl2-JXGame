#include <iostream>
#include <SDL.h>
#include <string>
#include <iostream>
#include "texture.h"
#include "LTexture.cpp"
#include <stdexcept>

SDL_Window* gWindow;

SDL_Renderer* gReneder;

const int HEIEGHT_WINDOW = 640;

const int WEIGHT_WINDOW = 480;

const int TOTAL_BUTTONS = 4;

const int BUTTON_WIDTH = 300;

const int BUTTON_HEIGHT = 200;

enum LButtonSprite {

    BUTTON_SPRITE_MOUSE_OUT,
    BUTTON_SPRITE_MOUSE_OVER_MOTION,
    BUTTON_SPRITE_MOUSE_DOWN,
    BUTTON_SPRITE_MOUSE_UP,
    BUTTON_SPRITE_MOUSE_TOTAL

};

SDL_Rect gSpriteClips[ BUTTON_SPRITE_MOUSE_TOTAL ];

LTexture gButtonSpriteSheetTexture;

class LButton{

    public : 
        LButton();

        void setPosition(int x, int y);

        void handleEvent(SDL_Event* e);

        void render();

    private :    

        SDL_Point mPosition;

        LButtonSprite gCurrentSprite;
};

LButton gButtons[ TOTAL_BUTTONS ]; 

void init(){

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        throw std::runtime_error(std::string(SDL_GetError()));
    }
    
    gWindow = SDL_CreateWindow("Mouse Events", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WEIGHT_WINDOW, HEIEGHT_WINDOW, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (!gWindow)
    {
        throw std::runtime_error(std::string(SDL_GetError()));
    }

    gReneder = SDL_CreateRenderer(gWindow,-1, SDL_RENDERER_ACCELERATED);

     gButtonSpriteSheetTexture = LTexture( gReneder );

}

void close(){

    SDL_DestroyWindow(gWindow);

    SDL_DestroyRenderer(gReneder);

    gReneder = nullptr;

    gWindow = nullptr;

}

bool loadMedia(){
     
    if (!gButtonSpriteSheetTexture.loadFromFile("button.png")) {
        std::cout << "\n@@@----------------------@\n";
        throw std::runtime_error("Failed to load button sprite texture! SDL Error: " + std::string(SDL_GetError()));
        return false;
    }

    for (int i = 0; i < BUTTON_SPRITE_MOUSE_TOTAL; i++)
    {
        gSpriteClips[i].x = 0;

        gSpriteClips[i].y = i * 200;

        gSpriteClips[i].w = BUTTON_WIDTH;

        gSpriteClips[i].h = BUTTON_HEIGHT;
    }
    
    gButtons[ 0 ].setPosition( 0, 0 );
	gButtons[ 1 ].setPosition( WEIGHT_WINDOW - BUTTON_WIDTH, 0 );
	gButtons[ 2 ].setPosition( 0, HEIEGHT_WINDOW - BUTTON_HEIGHT );
	gButtons[ 3 ].setPosition( WEIGHT_WINDOW - BUTTON_WIDTH, HEIEGHT_WINDOW - BUTTON_HEIGHT );

    return true;
}

LButton::LButton(){

    mPosition.x = 0;
    mPosition.y = 0;

    gCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;

}

void LButton::setPosition(int x, int y){
    
    mPosition.x = x;
    
    mPosition.y = y;
}

void LButton::handleEvent(SDL_Event* e){

    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
    {
       int x, y;
       
       bool inside = true;

       SDL_GetMouseState(&x, &y);

       if (x < mPosition.x)
       {
            inside = false;
       }
       else if (x > mPosition.x + BUTTON_WIDTH)
       {
            inside = false;
       }
       else if (y < mPosition.y)
       {
            inside = false;
       }
       else if (y > mPosition.y + BUTTON_HEIGHT)
       {
            inside = false;
       }
       
       if (!inside)
       {
       
        gCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
       
       }else{

        switch (e->type)
        {
        case SDL_MOUSEMOTION:
            gCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
            break;
        case SDL_MOUSEBUTTONDOWN:
         gCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
            break;
         case SDL_MOUSEBUTTONUP:
         gCurrentSprite = BUTTON_SPRITE_MOUSE_UP;    
            break;
        }
    }
       
       
       

    }
    
}

void LButton::render(){

    gButtonSpriteSheetTexture.render(mPosition.x, mPosition.y, &gSpriteClips[gCurrentSprite]);

}

int main(){

    SDL_Event e;

    bool quit = false;

    try
    {
        init();
        
        loadMedia();

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

            for( int i = 0; i < TOTAL_BUTTONS; ++i )
            {
                gButtons[ i ].handleEvent( &e );
            }
                
                
        }
            for( int i = 0; i < TOTAL_BUTTONS; ++i )
                {
                    gButtons[ i ].render();
                }

            SDL_RenderPresent(gReneder);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    close();
    return 0;
}