#include "cpu.hpp"
#include "display.hpp"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <SDL.h>

int main() {
    try {
        bool quit = false;
        SDL_Event e;
        CPU cpu;
        cpu.load_rom("../tests/1-ibm-logo.ch8"); // Load your ROM file here
        while (!quit) {
            // Handle window events
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
            }
            cpu.step(); // Execute a single CPU cycle
            SDL_Delay(16); // ~60 FPS
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
