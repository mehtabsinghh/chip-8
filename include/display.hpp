#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <SDL.h>
#include <cstdint>
#include <array>

static constexpr int WIDTH = 64;
static constexpr int HEIGHT = 32;

class Display {
private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    // 0 = off, 1 = on
    int scale;
    std::array<uint8_t, WIDTH * HEIGHT> pixels{};
public:
    Display(int scale = 10);
    ~Display();

    /*
    Clear the display.
    */
    void clear_screen();

    /*
    Draw a sprite at (x, y) with n rows.
    Returns true if there was a collision (i.e., if a pixel was turned off).
    */
    bool draw_sprite(int x, int y, const std::uint8_t* sprite, int n);

    /*
    Render the display to the screen.
    */
    void render();

};

#endif // DISPLAY_HPP