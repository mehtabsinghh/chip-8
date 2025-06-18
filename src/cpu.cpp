#include "cpu.hpp"

std::uint16_t CPU::fetch() {
    // Get both halves of instruction from memory
    auto byte1 = memory[PC];
    auto byte2 = memory[PC+1];

    PC += 2; // Incremented ready for next instruction

    // Combine both bytes into 16-bit instruction
    auto instruction = (byte1 << 8) | byte2;

    return instruction;
}
