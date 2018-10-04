#include "Miscellaneous.hpp"

namespace nsfgbe {
namespace instr {

void daa(Emulator &emulator, Word operand) {
    Word value = emulator.cpu.registers.a;

    if (emulator.cpu.getFlag(FLAG_SUBTRACT)) {
        if (emulator.cpu.getFlag(FLAG_HALF_CARRY)) {
            value -= 0x06;
        }
        if (emulator.cpu.getFlag(FLAG_CARRY)) {
            value -= 0x60;
        }
        value &= 0xFF;
    } else {
        if ((value & 0x0F) > 0x09 || emulator.cpu.getFlag(FLAG_HALF_CARRY)) {
            value += 0x06;
        }
        if (value > 0x9F || emulator.cpu.getFlag(FLAG_CARRY)) {
            value += 0x60;
        }
    }

    emulator.cpu.registers.a = static_cast<Byte>(value);

    emulator.cpu.setFlag(FLAG_ZERO, emulator.cpu.registers.a == 0);
    emulator.cpu.resetFlag(FLAG_HALF_CARRY);
    if (value > 0xFF) {
        emulator.cpu.setFlag(FLAG_CARRY);
    }
}

void cpl(Emulator &emulator, Word operand) {
    emulator.cpu.registers.a = ~emulator.cpu.registers.a;

    emulator.cpu.setFlag(FLAG_SUBTRACT | FLAG_HALF_CARRY);
}

void ccf(Emulator &emulator, Word operand) {
    emulator.cpu.setFlag(FLAG_CARRY, !emulator.cpu.getFlag(FLAG_CARRY));

    emulator.cpu.resetFlag(FLAG_SUBTRACT | FLAG_HALF_CARRY);
}

void scf(Emulator &emulator, Word operand) {
    emulator.cpu.resetFlag(FLAG_SUBTRACT | FLAG_HALF_CARRY);
    emulator.cpu.setFlag(FLAG_CARRY);
}

void nop(Emulator &emulator, Word operand) {
}

void halt(Emulator &emulator, Word operand) {
    emulator.cpu.halted = true;
}

void ei(Emulator &emulator, Word operand) {
    emulator.interruptManager.scheduleInterruptEnable();
}

void di(Emulator &emulator, Word operand) {
    emulator.interruptManager.scheduleInterruptDisable();
}

}
}
