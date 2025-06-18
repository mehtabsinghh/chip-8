#ifndef CPU_HPP
#define CPU_HPP

#include "display.hpp"
#include <cstdint>
#include <vector>

class CPU {
private:
    Display display;
    std::uint8_t memory[4096];        // Chip-8 has 4Kb of memory
    std::uint16_t I;                  // Points to some address in memory
    std::uint8_t registers[16];       // V0 through VF
    std::uint16_t PC;                 // Program counter
    std::vector<std::uint16_t> stack; // Stack for 16-bit registers
    std::uint8_t delay_timer;
    std::uint8_t sound_timer;
public:
    CPU() : PC(200), delay_timer(0), sound_timer(0) {
        std::uint8_t font_data[] = {
            0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
            0x20, 0x60, 0x20, 0x20, 0x70, // 1
            0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
            0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
            0x90, 0x90, 0xF0, 0x10, 0x10, // 4
            0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
            0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
            0xF0, 0x10, 0x20, 0x40, 0x40, // 7
            0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
            0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
            0xF0, 0x90, 0xF0, 0x90, 0x90, // A
            0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
            0xF0, 0x80, 0x80, 0x80, 0xF0, // C
            0xE0, 0x90, 0x90, 0x90, 0xE0, // D
            0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
            0xF0, 0x80, 0xF0, 0x80, 0x80  // F
        };
        memcpy(&memory[0x50], font_data, 80);

    }

    /*
     * Load a program into memory starting at address 0x200.
     * The program should be a vector of bytes.
     */
    std::uint16_t fetch();

    /*
     * Execute a single instruction.
     */
    void execute(std::uint16_t instruction);

    /*
     * Execute a single CPU cycle.
     */
    void step();
};

#endif // CPU_HPP