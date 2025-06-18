#ifndef CPU_HPP
#define CPU_HPP

#include "display.hpp"
#include <cstdint>
#include <vector>
#include <array>
#include <string>

class CPU {
private:
    Display display;
    std::array<std::uint8_t, 4096> memory;        // Chip-8 has 4Kb of memory
    std::uint16_t I;                  // Points to some address in memory
    std::array<std::uint8_t, 16> registers;       // V0 through VF
    std::uint16_t PC;                 // Program counter
    std::vector<std::uint16_t> stack; // Stack for 16-bit registers
    std::uint8_t delay_timer;
    std::uint8_t sound_timer;

    static constexpr std::size_t FONT_ADDR = 0x50;
    static constexpr std::size_t PROGRAM_START = 0x200;
    static constexpr std::array<std::uint8_t, 80> font_data = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF8, 0x10, 0xf8}; // A-F
    

public:
    CPU() : PC(PROGRAM_START), delay_timer(0), sound_timer(0) {
        std::copy(font_data.begin(), font_data.end(), &memory[FONT_ADDR]);

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

    void load_rom(const std::string& path);
};

#endif // CPU_HPP