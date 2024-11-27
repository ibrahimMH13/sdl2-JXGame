#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

// Screen dimensions
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Function to render text
void renderText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect dstRect = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Initialize SDL_ttf
    if (TTF_Init() < 0) {
        std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
        return -1;
    }

    // Create SDL window and renderer
    SDL_Window* window = SDL_CreateWindow(
        "Guessing Game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Load font
    TTF_Font* font = TTF_OpenFont("/System/Library/Fonts/SFNS.ttf", 24); // Ensure "arial.ttf" is in the same directory or provide the full path
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    // Randomly generate a secret number
    srand(static_cast<unsigned>(time(nullptr)));
    int secretNumber = rand() % 100 + 1;
    int userGuess = -1;

    // Game state
    std::string message = "Guess a number between 1 and 100!";
    SDL_Color textColor = { 255, 255, 255, 255 };
    bool running = true;

    // Main game loop
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym >= SDLK_0 && event.key.keysym.sym <= SDLK_9) {
                    int key = event.key.keysym.sym - SDLK_0;

                    // Add the guessed number logic
                    if (userGuess == -1) {
                        userGuess = key;
                    }
                    else {
                        userGuess = userGuess * 10 + key;
                    }
                }
                else if (event.key.keysym.sym == SDLK_RETURN) {
                    // Check guess when Enter is pressed
                    if (userGuess != -1) {
                        if (userGuess == secretNumber) {
                            message = "Correct! You win!";
                        }
                        else if (userGuess < secretNumber) {
                            message = "Too low! Try again.";
                        }
                        else {
                            message = "Too high! Try again.";
                        }
                        userGuess = -1; // Reset for the next guess
                    }
                }
                else if (event.key.keysym.sym == SDLK_BACKSPACE) {
                    // Clear the guess
                    userGuess = -1;
                }
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render the main message
        renderText(renderer, font, message, 50, 50, textColor);

        // Render the user's current guess
        if (userGuess != -1) {
            renderText(renderer, font, "Your guess: " + std::to_string(userGuess), 50, 100, textColor);
        }

        // Present the renderer
        SDL_RenderPresent(renderer);
    }

    // Clean up
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
