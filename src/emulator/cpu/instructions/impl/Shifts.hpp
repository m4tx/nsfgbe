#ifndef GAMEBOY_EMULATOR_SHIFTS_H
#define GAMEBOY_EMULATOR_SHIFTS_H


#include <emulator/Emulator.hpp>
#include <emulator/cpu/instructions/ByteValue.hpp>

namespace nsfgbe {
namespace instr {

/** Rotate A left. Old bit 7 to Carry flag. */
void rlca(Emulator &emulator, Word operand);

/** Rotate A left through Carry flag. */
void rla(Emulator &emulator, Word operand);

/** Rotate A right. Old bit 0 to Carry flag. */
void rrca(Emulator &emulator, Word operand);

/** Rotate A right through Carry flag. */
void rra(Emulator &emulator, Word operand);

/** Rotate n left. Old bit 7 to Carry flag. */
template<ByteArg R>
void rlc(Emulator &emulator, Word operand) {
    ByteValue<R> value(emulator);
    Byte oldValue = value;
    value <<= 1;
    value |= oldValue >> 7;

    emulator.cpu.resetFlag(FLAG_SUBTRACT | FLAG_HALF_CARRY);
    emulator.cpu.setFlag(FLAG_ZERO, value == 0);
    emulator.cpu.setFlag(FLAG_CARRY, oldValue >> 7);
}

/** Rotate n left through Carry flag. */
template<ByteArg R>
void rl(Emulator &emulator, Word operand) {
    ByteValue<R> value(emulator);
    Byte oldValue = value;
    value <<= 1;
    value |= emulator.cpu.getFlag(FLAG_CARRY);

    emulator.cpu.resetFlag(FLAG_SUBTRACT | FLAG_HALF_CARRY);
    emulator.cpu.setFlag(FLAG_ZERO, value == 0);
    emulator.cpu.setFlag(FLAG_CARRY, oldValue >> 7);
}

/** Rotate n right. Old bit 0 to Carry flag. */
template<ByteArg R>
void rrc(Emulator &emulator, Word operand) {
    ByteValue<R> value(emulator);
    Byte oldValue = value;
    value >>= 1;
    value |= (oldValue & 1) << 7;

    emulator.cpu.resetFlag(FLAG_SUBTRACT | FLAG_HALF_CARRY);
    emulator.cpu.setFlag(FLAG_ZERO, value == 0);
    emulator.cpu.setFlag(FLAG_CARRY, (oldValue & 1) != 0);
}

/** Rotate n right through Carry flag. */
template<ByteArg R>
void rr(Emulator &emulator, Word operand) {
    ByteValue<R> value(emulator);
    Byte oldValue = value;
    value >>= 1;
    value |= (emulator.cpu.getFlag(FLAG_CARRY) << 7);

    emulator.cpu.resetFlag(FLAG_SUBTRACT | FLAG_HALF_CARRY);
    emulator.cpu.setFlag(FLAG_ZERO, value == 0);
    emulator.cpu.setFlag(FLAG_CARRY, (oldValue & 1) != 0);
}

/** Shift n left into Carry. LSB of n set to 0. */
template<ByteArg R>
void sla(Emulator &emulator, Word operand) {
    ByteValue<R> value(emulator);
    Byte oldValue = value;
    value <<= 1;

    emulator.cpu.resetFlag(FLAG_SUBTRACT | FLAG_HALF_CARRY);
    emulator.cpu.setFlag(FLAG_ZERO, value == 0);
    emulator.cpu.setFlag(FLAG_CARRY, oldValue >> 7);
}

/** Shift n right into Carry. MSB doesn't change. */
template<ByteArg R>
void sra(Emulator &emulator, Word operand) {
    ByteValue<R> value(emulator);
    Byte oldValue = value;
    value >>= 1;
    // Preserve the MSB
    value |= oldValue & 0x80;

    emulator.cpu.resetFlag(FLAG_SUBTRACT | FLAG_HALF_CARRY);
    emulator.cpu.setFlag(FLAG_ZERO, value == 0);
    emulator.cpu.setFlag(FLAG_CARRY, (oldValue & 1) != 0);
}

/** Shift n right into Carry. MSB set to 0. */
template<ByteArg R>
void srl(Emulator &emulator, Word operand) {
    ByteValue<R> value(emulator);
    Byte oldValue = value;
    value >>= 1;

    emulator.cpu.resetFlag(FLAG_SUBTRACT | FLAG_HALF_CARRY);
    emulator.cpu.setFlag(FLAG_ZERO, value == 0);
    emulator.cpu.setFlag(FLAG_CARRY, (oldValue & 1) != 0);
}


}
}


#endif //GAMEBOY_EMULATOR_SHIFTS_H
