#include <iostream>
#include "Arithmetic.hpp"

namespace gb {
namespace instr {

Byte addFlags(Emulator &emulator, Byte a, Byte b, Byte c) {
    Word newValue = static_cast<Word>(a) + b + c;

    emulator.cpu.resetFlag(FLAG_SUBTRACT);
    emulator.cpu.setFlag(FLAG_ZERO, static_cast<Byte>(newValue) == 0);
    emulator.cpu.setFlag(FLAG_CARRY, (newValue & 0xFF00) != 0);
    emulator.cpu.setFlag(
            FLAG_HALF_CARRY,
            (((static_cast<Word>(a) & 0x0F) + (b & 0x0F) + c) & 0xF0) != 0);

    return static_cast<Byte>(newValue);
}

void addImm8(Emulator &emulator, Word operand) {
    emulator.cpu.registers.a = addFlags(
            emulator, emulator.cpu.registers.a, static_cast<Byte>(operand));
}

void adcImm8(Emulator &emulator, Word operand) {
    emulator.cpu.registers.a = addFlags(
            emulator, emulator.cpu.registers.a,
            static_cast<Byte>(operand),
            static_cast<Byte>(emulator.cpu.getFlag(FLAG_CARRY)));
}

Byte subFlags(Emulator &emulator, Byte a, Byte b, Byte c) {
    Byte result = a - b - c;

    emulator.cpu.setFlag(FLAG_SUBTRACT);
    emulator.cpu.setFlag(FLAG_ZERO, result == 0);
    emulator.cpu.setFlag(
            FLAG_CARRY,
            static_cast<Word>(a) < static_cast<Word>(b) + c);
    emulator.cpu.setFlag(FLAG_HALF_CARRY, (a & 0x0F) < (b & 0x0F) + c);

    return result;
}

void subImm8(Emulator &emulator, Word operand) {
    emulator.cpu.registers.a = subFlags(
            emulator, emulator.cpu.registers.a, static_cast<Byte>(operand));
}

void sbcImm8(Emulator &emulator, Word operand) {
    emulator.cpu.registers.a = subFlags(
            emulator, emulator.cpu.registers.a,
            static_cast<Byte>(operand),
            static_cast<Byte>(emulator.cpu.getFlag(FLAG_CARRY)));
}

void andImm8(Emulator &emulator, Word operand) {
    emulator.cpu.registers.a &= operand;

    emulator.cpu.resetFlag(ALL_FLAGS);
    emulator.cpu.setFlag(FLAG_HALF_CARRY);
    emulator.cpu.setFlag(FLAG_ZERO, emulator.cpu.registers.a == 0);
}

void orImm8(Emulator &emulator, Word operand) {
    emulator.cpu.registers.a |= operand;

    emulator.cpu.resetFlag(ALL_FLAGS);
    emulator.cpu.setFlag(FLAG_ZERO, emulator.cpu.registers.a == 0);
}

void xorImm8(Emulator &emulator, Word operand) {
    emulator.cpu.registers.a ^= operand;

    emulator.cpu.resetFlag(ALL_FLAGS);
    emulator.cpu.setFlag(FLAG_ZERO, emulator.cpu.registers.a == 0);
}

void cpImm8(Emulator &emulator, Word operand) {
    subFlags(emulator, ByteValue<ARG_REG_A>(emulator),
             static_cast<Byte>(operand));
}

void addSpImm8(Emulator &emulator, Word operand) {
    emulator.cpu.registers.sp = addWordByteFlags(
            emulator,
            emulator.cpu.registers.sp,
            static_cast<SignedByte>(operand));
}

Word addWordByteFlags(Emulator &emulator, Word a, SignedByte b) {
    emulator.cpu.resetFlag(FLAG_ZERO | FLAG_SUBTRACT);
    emulator.cpu.setFlag(
            FLAG_CARRY,
            ((static_cast<uint32_t>(a & 0xFF) + (b & 0xFF)) & 0xFF00) != 0);
    emulator.cpu.setFlag(
            FLAG_HALF_CARRY, (((a & 0x0F) + (b & 0x0F)) & 0xF0) != 0);

    return a + b;
}

}
}
