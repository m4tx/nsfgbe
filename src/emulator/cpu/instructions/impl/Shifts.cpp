#include "Shifts.hpp"

namespace nsfgbe {
namespace instr {

void rlca(Emulator &emulator, Word operand) {
    Byte value = emulator.cpu.registers.a;
    emulator.cpu.registers.a = (value << 1) + (value >> 7);

    emulator.cpu.resetFlag(CPUFlags::ZERO | CPUFlags::SUBTRACT | CPUFlags::HALF_CARRY);
    emulator.cpu.setFlag(CPUFlags::CARRY, value >> 7);
}

void rla(Emulator &emulator, Word operand) {
    Byte value = emulator.cpu.registers.a;
    emulator.cpu.registers.a = (value << 1) + emulator.cpu.getFlag(CPUFlags::CARRY);

    emulator.cpu.resetFlag(CPUFlags::ZERO | CPUFlags::SUBTRACT | CPUFlags::HALF_CARRY);
    emulator.cpu.setFlag(CPUFlags::CARRY, value >> 7);
}

void rrca(Emulator &emulator, Word operand) {
    Byte value = emulator.cpu.registers.a;
    emulator.cpu.registers.a = static_cast<Byte>(
            (value >> 1) | (value & 1) << 7);

    emulator.cpu.resetFlag(CPUFlags::ZERO | CPUFlags::SUBTRACT | CPUFlags::HALF_CARRY);
    emulator.cpu.setFlag(CPUFlags::CARRY, (value & 1) != 0);
}

void rra(Emulator &emulator, Word operand) {
    Byte value = emulator.cpu.registers.a;
    emulator.cpu.registers.a =
            (value >> 1) | (emulator.cpu.getFlag(CPUFlags::CARRY) << 7);

    emulator.cpu.resetFlag(CPUFlags::ZERO | CPUFlags::SUBTRACT | CPUFlags::HALF_CARRY);
    emulator.cpu.setFlag(CPUFlags::CARRY, (value & 1) != 0);
}

}
}
