#include "Miscellaneous.hpp"

namespace nsfgbe {
namespace instr {

void daa(Emulator &emulator, Word operand) {
    Word value = emulator.cpu.registers.a;

    if (emulator.cpu.getFlag(CPUFlags::SUBTRACT)) {
        if (emulator.cpu.getFlag(CPUFlags::HALF_CARRY)) {
            value -= 0x06;
        }
        if (emulator.cpu.getFlag(CPUFlags::CARRY)) {
            value -= 0x60;
        }
        value &= 0xFF;
    } else {
        if ((value & 0x0F) > 0x09 || emulator.cpu.getFlag(CPUFlags::HALF_CARRY)) {
            value += 0x06;
        }
        if (value > 0x9F || emulator.cpu.getFlag(CPUFlags::CARRY)) {
            value += 0x60;
        }
    }

    emulator.cpu.registers.a = static_cast<Byte>(value);

    emulator.cpu.setFlag(CPUFlags::ZERO, emulator.cpu.registers.a == 0);
    emulator.cpu.resetFlag(CPUFlags::HALF_CARRY);
    if (value > 0xFF) {
        emulator.cpu.setFlag(CPUFlags::CARRY);
    }
}

void cpl(Emulator &emulator, Word operand) {
    emulator.cpu.registers.a = ~emulator.cpu.registers.a;

    emulator.cpu.setFlag(CPUFlags::SUBTRACT | CPUFlags::HALF_CARRY);
}

void ccf(Emulator &emulator, Word operand) {
    emulator.cpu.setFlag(CPUFlags::CARRY, !emulator.cpu.getFlag(CPUFlags::CARRY));

    emulator.cpu.resetFlag(CPUFlags::SUBTRACT | CPUFlags::HALF_CARRY);
}

void scf(Emulator &emulator, Word operand) {
    emulator.cpu.resetFlag(CPUFlags::SUBTRACT | CPUFlags::HALF_CARRY);
    emulator.cpu.setFlag(CPUFlags::CARRY);
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
