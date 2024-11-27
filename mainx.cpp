#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();

enum keyPressSurfaces {
    KEY_PRESS_UP,
    KEY_PRESS_DOWN,
    KEY_PRESS_LEFT,
    KEY_PRESS_RIGHT,
    KEY_PRESS_DEFAULT,
    KEY_PRESS_TOTAL
};

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWorld = NULL;
SDL_Surface* loadSurface(std::string path); 
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_TOTAL];
SDL_Surface* gCurrentSurface = NULL;

int main(int argc, char* args[]) {
    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        if (!loadMedia()) {
            printf("Failed to load media!\n");
        } else {
            // Display image
            SDL_Rect destRect;
            destRect.x = 0;
            destRect.y = 0;
            destRect.w = SCREEN_WIDTH;
            destRect.h = SCREEN_HEIGHT;

            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_DEFAULT];
            // Wait for quit event
            SDL_Event e;
            bool quit = false;
            while (!quit) {
                while (SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                    else if (e.type == SDL_KEYDOWN)
                    {
                      switch (e.key.keysym.sym)
                      {
                      case SDLK_UP:
                        std::cout << "up key clicked\n";
                        gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_UP];
                        break;
                      case SDLK_DOWN:
                        std::cout << "down key clicked\n";
                        gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_DOWN];
                        break;
                      case SDLK_LEFT:
                         std::cout << "left key clicked\n";
                        gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_LEFT];
                      break;
                      case SDLK_RIGHT:
                        std::cout << "right key clicked\n";
                        gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_RIGHT];
                      break;
                      default:
                        std::cout << "deafult/any key clicked\n";
                        gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_DEFAULT];
                        break;
                      }
                    }
                    
                }

            SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
            
            SDL_UpdateWindowSurface(gWindow);

            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_DEFAULT];

            }

        }
    }

    close();
    return 0;
}

void close() {
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();
}

bool init() {
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    } else {
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        } else {
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    return success;
}

bool loadMedia() {
    bool success = true;

    // Ensure the file is named background_single.bmp
    gKeyPressSurfaces[KEY_PRESS_DEFAULT] = loadSurface("press.bmp");

    if (gKeyPressSurfaces[KEY_PRESS_DEFAULT] == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", "background_single.png", SDL_GetError());
        success = false;
    }

     gKeyPressSurfaces[KEY_PRESS_UP] = loadSurface("up.bmp"); printf("down loaded");
      printf("up loaded");
     if (gKeyPressSurfaces[KEY_PRESS_UP] == NULL)
     {
       printf("Unable to load PRESS UP image %s! SDL Error: %s\n", "up.bmp", SDL_GetError());
        success = false;
     }
     
     gKeyPressSurfaces[KEY_PRESS_DOWN] = loadSurface("down.bmp");
     if (gKeyPressSurfaces[KEY_PRESS_DOWN] == NULL)
     {
        printf("Unable to load PRESS DOWN image %s! SDL Error: %s\n", "down.bmp", SDL_GetError());
        success = false;
     }
     
    gKeyPressSurfaces[KEY_PRESS_LEFT] = loadSurface("left.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_LEFT] == NULL)
    {
        printf("Unable to load PRESS LEFT image %s! SDL Error: %s\n", "left.bmp", SDL_GetError());
        success = false;
    }
    
    gKeyPressSurfaces[KEY_PRESS_RIGHT] = loadSurface("right.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_RIGHT] == NULL)
    {
        printf("Unable to load PRESS RIGHT image %s! SDL Error: %s\n", "right.bmp", SDL_GetError());
        success = false;
    }
    
    return success;
}

SDL_Surface* loadSurface(std::string path){

    SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );

    if (loadedSurface == NULL)
    {
        printf("unable to load image %s,\n SDL ERR# %s\n",path.c_str(), SDL_GetError());
    }
    return loadedSurface;
}