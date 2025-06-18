#include "display.hpp"


Display::Display(int scale) : scale(scale) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error(SDL_GetError());
    }

    SDL_Window* window = SDL_CreateWindow(
        "Chip-8 Emulator",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH * scale, HEIGHT * scale,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        throw std::runtime_error(SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_DestroyWindow(window);
        throw std::runtime_error(SDL_GetError());
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set background color to black
}

Display::~Display() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Display::clear_screen() {
    pixels.fill(0);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

bool Display::draw_sprite(int x, int y, const std::uint8_t* sprite, int n) {
    // Ensure x and y are within bounds
    int startX = x & (WIDTH - 1);
    int startY = y & (HEIGHT - 1);


    bool collision = false;

    // Iterate over the sprite rows
    for (int row = 0; row < n; ++row) {
        auto dy = startY + row;
        if (dy >= HEIGHT) break; // Prevent drawing outside the display height

        auto rowBits = sprite[row];

        // Iterate over the bits in the row
        for (int bit = 0; bit < 8; ++bit) {
            auto dx = startX + bit;
            if (dx >= WIDTH) break; // Prevent drawing outside the display width

            // Check if the pixel is off (0) or on (1)
            bool pixelOff = (rowBits & (0x80 >> bit)) == 0;
            if (pixelOff) continue; // Skip if the pixel is off

            // Calculate the index in the pixel array
            size_t idx = dy * WIDTH + dx;
            if (pixels[idx]) {
                collision = true;
            }

            // Toggle the pixel state
            pixels[idx] ^= 1;
        }
    }
    
    render(); // Update the display after drawing the sprite 
    return collision;
}

void Display::render() {
    // Clear the renderer with black color
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer); 

    // Draw the pixels using white color
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (pixels[y * WIDTH + x]) {
                SDL_Rect rect{x * scale, y * scale, scale, scale};
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }

    // Present the renderer to the screen
    SDL_RenderPresent(renderer);
}