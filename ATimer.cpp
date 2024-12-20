#include <iostream>
#include <SDL.h>
#include <string>
#include <sstream>
#include <stdexcept>
#include "texture.h"
#include "LTexture.cpp"
#include "timer.h"
#include "AdvanceTimer.cpp"

const int WIDTH_SCREEN = 700;  // Corrected WEIGHT_SCREEN to WIDTH_SCREEN
const int HEIGHT_SCREEN = 700;

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

LTexture texture;
LTexture gStartPromptTexture;
LTexture gPausePromptTexture;

void init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("SDL_Init failed: " + std::string(SDL_GetError()));
    }
    if (TTF_Init() == -1) {
        throw std::runtime_error("TTF_Init failed: " + std::string(TTF_GetError()));
    }

    gWindow = SDL_CreateWindow("font", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               WIDTH_SCREEN, HEIGHT_SCREEN, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!gWindow) {
        throw std::runtime_error("SDL_CreateWindow failed: " + std::string(SDL_GetError()));
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!gRenderer) {
        throw std::runtime_error("SDL_CreateRenderer failed: " + std::string(SDL_GetError()));
    }

    texture = LTexture(gRenderer);
}

bool loadMedia() {
    if (!gStartPromptTexture.loadFromText("Press S to Start/Stop Timer", {0, 0, 0, 255})) {
        std::cerr << "Failed to load start prompt texture!\n";
        return false;
    }
    if (!gPausePromptTexture.loadFromText("Press P to Pause/Resume Timer", {0, 0, 0, 255})) {
        std::cerr << "Failed to load pause prompt texture!\n";
        return false;
    }
    return true;
}

void close() {
    gStartPromptTexture.free();
    gPausePromptTexture.free();
    texture.free();

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);

    gRenderer = nullptr;
    gWindow = nullptr;

    TTF_Quit();
    SDL_Quit();
}

int main() {
    SDL_Event e;
    bool quit = false;
    SDL_Color textColor = {0, 0, 0, 255};
    AdvanceTimer timer;
    std::stringstream timeText;

    try {
        init();
        if (
                !texture.setFontType("/System/Library/Fonts/SFNS.ttf",70)
            )
            {
              throw std::runtime_error("font issue" + std::string(TTF_GetError()));
            }
        gPausePromptTexture = texture;
        gStartPromptTexture = texture;
        while (!quit) {
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(gRenderer);

            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                } else if (e.type == SDL_KEYDOWN) {
                    if (e.key.keysym.sym == SDLK_s) {
                        if (timer.isStart()) {
                            timer.pause();
                        } else {
                            timer.start();
                        }
                    } else if (e.key.keysym.sym == SDLK_p) {
                        if (timer.isPause()) {
                            timer.resume();
                        } else {
                            timer.pause();
                        }
                    }
                }
            }

            timeText.str("");
            timeText << "Seconds since start time: " << (timer.getTicks() / 1000.f);

            if (!texture.loadFromText(timeText.str().c_str(), textColor)) {
                std::cerr << "Failed to render time texture!\n";
            }

            gStartPromptTexture.render((WIDTH_SCREEN - gStartPromptTexture.getWidth()) / 2, 0);
            gPausePromptTexture.render((WIDTH_SCREEN - gPausePromptTexture.getWidth()) / 2, gStartPromptTexture.getHeight());
            texture.render((WIDTH_SCREEN - texture.getWidth()) / 2, (HEIGHT_SCREEN - texture.getHeight()) / 2);

            SDL_RenderPresent(gRenderer);
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    close();
    return 0;
}
