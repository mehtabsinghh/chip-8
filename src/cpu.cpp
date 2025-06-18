#include "cpu.hpp"
#include <fstream>

std::uint16_t CPU::fetch() {
    // Get both halves of instruction from memory
    auto byte1 = memory[PC];
    auto byte2 = memory[PC+1];

    PC += 2; // Incremented ready for next instruction

    // Combine both bytes into 16-bit instruction
    auto instruction = (byte1 << 8) | byte2;

    return instruction;
}

/*
TODO:
00E0 (clear screen)
1NNN (jump)
6XNN (set register VX)
7XNN (add value to register VX)
ANNN (set index register I)
DXYN (display/draw)
*/
void CPU::execute(std::uint16_t instruction) {
    auto opcode = (instruction & 0xF000) >> 12; 
    auto x = (instruction & 0x0F00) >> 8;
    auto y = (instruction & 0x00F0) >> 4;
    auto n = instruction & 0x000F;
    auto nn = instruction & 0x00FF;
    auto nnn = instruction & 0x0FFF;

    switch (opcode) {
        case 0x0:
            // 0x00E0: Clear the display
            if (instruction == 0x00E0)
                display.clear_screen();
            break;
        case 0x1:
            // Jump to address nnn
            PC = nnn;
        case 0x2:
            break;
        case 0x3:
            break;
        case 0x4:
            break;
        case 0x5:
            break;
        case 0x6:
            // Set register Vx to nn
            registers[x] = nn;
            break;
        case 0x7:
            // Add nn to register Vx
            registers[x] += nn;
            break;
        case 0x8:
            break;
        case 0x9:
            break;
        case 0xA:
            I = nnn;
            break;
        case 0xB:
            break;
        case 0xC:
            break;
        case 0xD: {
            // Draw sprite at (Vx, Vy) with n rows
            auto xCoor = registers[x];
            auto yCoor = registers[y];
            std::uint8_t* sprite = &memory[I];
            bool collision = display.draw_sprite(xCoor, yCoor, sprite, n);

            // Set VF to 1 if there was a collision, 0 otherwise
            registers[0xF] = collision ? 1 : 0;
            break;
        }
        case 0xE:
            break;
        case 0xF:
            break;
        default:
            break;
    }
}

void CPU::step() {
    auto instruction = fetch();
    execute(instruction);
}

void CPU::load_rom(const std::string& path) {
    // 1) open in binary+ate (ate lets us immediately tellg() to find size)
    std::ifstream rom(path, std::ios::binary | std::ios::ate);
    if (!rom) {
        throw std::runtime_error("Failed to open ROM: " + path);
    }

    // 2) get size
    std::streamsize size = rom.tellg();
    rom.seekg(0, std::ios::beg);

    // 3) bounds check against memory capacity
    if (size <= 0 || static_cast<std::size_t>(size) > (memory.size() - PROGRAM_START)) {
        throw std::runtime_error("ROM is too large to fit in memory");
    }

    // 4) read directly into memory at 0x200
    if (!rom.read(reinterpret_cast<char*>(&memory[PROGRAM_START]), size)) {
        throw std::runtime_error("Failed to read entire ROM into memory");
    }

    // 5) set program counter to start of ROM
    PC = PROGRAM_START;
}
