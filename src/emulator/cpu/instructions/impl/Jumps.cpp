#include "Jumps.hpp"

namespace gb {
namespace instr {

void jp(Emulator &emulator, Word operand) {
    emulator.cpu.registers.pc = operand;
}

void jpNz(Emulator &emulator, Word operand) {
    if (!emulator.cpu.getFlag(FLAG_ZERO)) {
        jp(emulator, operand);
    }
}

void jpZ(Emulator &emulator, Word operand) {
    if (emulator.cpu.getFlag(FLAG_ZERO)) {
        jp(emulator, operand);
    }
}

void jpNc(Emulator &emulator, Word operand) {
    if (!emulator.cpu.getFlag(FLAG_CARRY)) {
        jp(emulator, operand);
    }
}

void jpC(Emulator &emulator, Word operand) {
    if (emulator.cpu.getFlag(FLAG_CARRY)) {
        jp(emulator, operand);
    }
}

void jpPtrHl(Emulator &emulator, Word operand) {
    emulator.cpu.registers.pc = emulator.cpu.registers.hl;
}

void jr(Emulator &emulator, Word operand) {
    emulator.cpu.registers.pc += static_cast<int8_t>(operand);
}

void jrNz(Emulator &emulator, Word operand) {
    if (!emulator.cpu.getFlag(FLAG_ZERO)) {
        jr(emulator, operand);
    }
}

void jrZ(Emulator &emulator, Word operand) {
    if (emulator.cpu.getFlag(FLAG_ZERO)) {
        jr(emulator, operand);
    }
}

void jrNc(Emulator &emulator, Word operand) {
    if (!emulator.cpu.getFlag(FLAG_CARRY)) {
        jr(emulator, operand);
    }
}

void jrC(Emulator &emulator, Word operand) {
    if (emulator.cpu.getFlag(FLAG_CARRY)) {
        jr(emulator, operand);
    }
}

}
}
