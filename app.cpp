#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Function prototypes
bool init();
bool loadMedia();
void close();
SDL_Texture* loadTexture(std::string path);

// Global variables
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gBackgroundTexture = NULL;
SDL_Texture* gKeyPressTextures[5]; // Array for key press textures

bool init() {
    bool success = true;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    } else {
        // Create window
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        } else {
            // Create renderer
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL) {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            } else {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }

    return success;
}

SDL_Texture* loadTexture(std::string path) {
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == NULL) {
        printf("Unable to load image %s! IMG Error: %s\n", path.c_str(), IMG_GetError());
    } else {
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

bool loadMedia() {
    bool success = true;

    // Load background texture
    gBackgroundTexture = loadTexture("background_single.png");
    if (gBackgroundTexture == NULL) {
        printf("Failed to load background texture!\n");
        success = false;
    }

    // Load key press textures
    gKeyPressTextures[0] = loadTexture("player_fish.png");
    gKeyPressTextures[1] = loadTexture("smallGears.png");
    gKeyPressTextures[2] = loadTexture("down.bmp");
    gKeyPressTextures[3] = loadTexture("left.bmp");
    gKeyPressTextures[4] = loadTexture("right.bmp");

    for (int i = 0; i < 5; ++i) {
        if (gKeyPressTextures[i] == NULL) {
            printf("Failed to load key press texture %d!\n", i);
            success = false;
        }
    }

    return success;
}

void close() {
    // Free textures
    SDL_DestroyTexture(gBackgroundTexture);
    gBackgroundTexture = NULL;

    for (int i = 0; i < 5; ++i) {
        SDL_DestroyTexture(gKeyPressTextures[i]);
        gKeyPressTextures[i] = NULL;
    }

    // Destroy renderer and window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = NULL;
    gWindow = NULL;

    // Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* args[]) {
    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        if (!loadMedia()) {
            printf("Failed to load media!\n");
        } else {
            bool quit = false;
            SDL_Event e;
            SDL_Texture* currentTexture = gKeyPressTextures[0];

            while (!quit) {
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    } else if (e.type == SDL_KEYDOWN) {
                        switch (e.key.keysym.sym) {
                            case SDLK_UP:
                                currentTexture = gKeyPressTextures[1];
                                break;
                            case SDLK_DOWN:
                                currentTexture = gKeyPressTextures[2];
                                break;
                            case SDLK_LEFT:
                                currentTexture = gKeyPressTextures[3];
                                break;
                            case SDLK_RIGHT:
                                currentTexture = gKeyPressTextures[4];
                                break;
                            default:
                                currentTexture = gKeyPressTextures[0];
                                break;
                        }
                    }
                }

				SDL_Rect destRect = {100, 100, 200, 200}; 
                // Render current texture
                SDL_RenderClear(gRenderer);
                SDL_RenderCopy(gRenderer, gBackgroundTexture, NULL, NULL);
                SDL_RenderCopy(gRenderer, currentTexture, NULL, &destRect);
                SDL_RenderPresent(gRenderer);
            }
        }
    }

    close();
    return 0;
}
