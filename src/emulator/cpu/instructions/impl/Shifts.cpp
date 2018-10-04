#include "Shifts.hpp"

namespace gb {
namespace instr {

void rlca(Emulator &emulator, Word operand) {
    Byte value = emulator.cpu.registers.a;
    emulator.cpu.registers.a = (value << 1) + (value >> 7);

    emulator.cpu.resetFlag(FLAG_ZERO | FLAG_SUBTRACT | FLAG_HALF_CARRY);
    emulator.cpu.setFlag(FLAG_CARRY, value >> 7);
}

void rla(Emulator &emulator, Word operand) {
    Byte value = emulator.cpu.registers.a;
    emulator.cpu.registers.a = (value << 1) + emulator.cpu.getFlag(FLAG_CARRY);

    emulator.cpu.resetFlag(FLAG_ZERO | FLAG_SUBTRACT | FLAG_HALF_CARRY);
    emulator.cpu.setFlag(FLAG_CARRY, value >> 7);
}

void rrca(Emulator &emulator, Word operand) {
    Byte value = emulator.cpu.registers.a;
    emulator.cpu.registers.a = static_cast<Byte>(
            (value >> 1) | (value & 1) << 7);

    emulator.cpu.resetFlag(FLAG_ZERO | FLAG_SUBTRACT | FLAG_HALF_CARRY);
    emulator.cpu.setFlag(FLAG_CARRY, (value & 1) != 0);
}

void rra(Emulator &emulator, Word operand) {
    Byte value = emulator.cpu.registers.a;
    emulator.cpu.registers.a =
            (value >> 1) | (emulator.cpu.getFlag(FLAG_CARRY) << 7);

    emulator.cpu.resetFlag(FLAG_ZERO | FLAG_SUBTRACT | FLAG_HALF_CARRY);
    emulator.cpu.setFlag(FLAG_CARRY, (value & 1) != 0);
}

}
}
