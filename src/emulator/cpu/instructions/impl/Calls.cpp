#include "Calls.hpp"

namespace nsfgbe {
namespace instr {

void callImm16(Emulator &emulator, Word operand) {
    pushImm16(emulator, emulator.cpu.registers.pc);
    emulator.cpu.registers.pc = operand;
}

void callNzImm16(Emulator &emulator, Word operand) {
    if (!emulator.cpu.getFlag(FLAG_ZERO)) {
        callImm16(emulator, operand);
    }
}

void callZImm16(Emulator &emulator, Word operand) {
    if (emulator.cpu.getFlag(FLAG_ZERO)) {
        callImm16(emulator, operand);
    }
}

void callNcImm16(Emulator &emulator, Word operand) {
    if (!emulator.cpu.getFlag(FLAG_CARRY)) {
        callImm16(emulator, operand);
    }
}

void callCImm16(Emulator &emulator, Word operand) {
    if (emulator.cpu.getFlag(FLAG_CARRY)) {
        callImm16(emulator, operand);
    }
}

void ret(Emulator &emulator, Word operand) {
    emulator.cpu.registers.pc = popRet16(emulator);
}

void retNz(Emulator &emulator, Word operand) {
    if (!emulator.cpu.getFlag(FLAG_ZERO)) {
        ret(emulator, operand);
    }
}

void retZ(Emulator &emulator, Word operand) {
    if (emulator.cpu.getFlag(FLAG_ZERO)) {
        ret(emulator, operand);
    }
}

void retNc(Emulator &emulator, Word operand) {
    if (!emulator.cpu.getFlag(FLAG_CARRY)) {
        ret(emulator, operand);
    }
}

void retC(Emulator &emulator, Word operand) {
    if (emulator.cpu.getFlag(FLAG_CARRY)) {
        ret(emulator, operand);
    }
}

void reti(Emulator &emulator, Word operand) {
    ret(emulator, operand);
    emulator.interruptManager.scheduleInterruptEnable();
}

}
}
