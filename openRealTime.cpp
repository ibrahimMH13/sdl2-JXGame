#include <iostream>
#include <SDL.h>
#include <string>
#include <iostream>
#include "texture.h"
#include "LTexture.cpp"
#include <stdexcept>

// Structure for draggable shapes
struct Shape {
    SDL_Rect rect;       // Shape position and size
    SDL_Texture* texture; // Shape texture
    bool placed;         // Whether the shape is correctly placed
};

// Function to load texture
SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer) {
    SDL_Surface* tempSurface = IMG_Load(path.c_str());
    if (!tempSurface) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    return texture;
}

// Check if two rectangles overlap
bool isOverlapping(SDL_Rect a, SDL_Rect b) {
    return (a.x < b.x + b.w && a.x + a.w > b.x && a.y < b.y + b.h && a.y + a.h > b.y);
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0 || !(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "Failed to initialize SDL or SDL_image!" << std::endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Shape Cave", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Load textures
    SDL_Texture* circleTexture = loadTexture("arrow.png", renderer);
    SDL_Texture* targetTexture = loadTexture("colors.png", renderer);

    if (!circleTexture || !targetTexture) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return -1;
    }

    // Initialize shapes
    Shape circle = {{100, 100, 100, 100}, circleTexture, false};
    SDL_Rect target = {400, 300, 100, 100};

    bool running = true;
    SDL_Event event;
    bool dragging = false;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX = event.button.x;
                int mouseY = event.button.y;

                SDL_Point mousePoint = {mouseX, mouseY}; // Fixed: Create a named SDL_Point
                if (!circle.placed && SDL_PointInRect(&mousePoint, &circle.rect)) {
                    dragging = true;
                }
            }

            if (event.type == SDL_MOUSEBUTTONUP) {
                dragging = false;

                // Check if circle is placed on the target
                if (isOverlapping(circle.rect, target)) {
                    circle.rect.x = target.x;
                    circle.rect.y = target.y;
                    circle.placed = true;
                }
            }

            if (event.type == SDL_MOUSEMOTION && dragging) {
                circle.rect.x = event.motion.x - circle.rect.w / 2;
                circle.rect.y = event.motion.y - circle.rect.h / 2;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Render target and shape
        SDL_RenderCopy(renderer, targetTexture, NULL, &target);
        SDL_RenderCopy(renderer, circle.texture, NULL, &circle.rect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(circle.texture);
    SDL_DestroyTexture(targetTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
