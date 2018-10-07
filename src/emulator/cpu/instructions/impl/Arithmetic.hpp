#ifndef GAMEBOY_EMULATOR_ARITHMETIC_H
#define GAMEBOY_EMULATOR_ARITHMETIC_H


#include <emulator/Emulator.hpp>
#include <emulator/cpu/instructions/ByteValue.hpp>
#include <emulator/cpu/instructions/WordValue.hpp>

namespace nsfgbe {
namespace instr {

// ####################################
// 8-Bit ALU
// ####################################

/**
 * Perform a + b + c addition, set the flags and return the result.
 * (not an actual instruction)
 */
Byte addFlags(Emulator &emulator, Byte a, Byte b, Byte c = 0);

/** Add n to A. */
void addImm8(Emulator &emulator, Word operand);

/** Add n to A. */
template<ByteArg R>
void add(Emulator &emulator, Word operand) {
    addImm8(emulator, ByteValue<R>(emulator));
}

/** Add n + Carry flag to A. */
void adcImm8(Emulator &emulator, Word operand);

/** Add n + Carry flag to A. */
template<ByteArg R>
void adc(Emulator &emulator, Word operand) {
    adcImm8(emulator, ByteValue<R>(emulator));
}

/**
 * Perform a - b - c subtraction, set the flags and return the result.
 * (not an actual instruction)
 */
Byte subFlags(Emulator &emulator, Byte a, Byte b, Byte c = 0);

/** Subtract n from A. */
void subImm8(Emulator &emulator, Word operand);

/** Subtract R from A. */
template<ByteArg R>
void sub(Emulator &emulator, Word operand) {
    subImm8(emulator, ByteValue<R>(emulator));
}

/** Subtract n + Carry flag from A. */
void sbcImm8(Emulator &emulator, Word operand);

/** Subtract n + Carry flag from A. */
template<ByteArg R>
void sbc(Emulator &emulator, Word operand) {
    sbcImm8(emulator, ByteValue<R>(emulator));
}

/** Logical AND n with register A, result in A. */
void andImm8(Emulator &emulator, Word operand);

/** Logical AND n with register A, result in A. */
template<ByteArg R>
void andR8(Emulator &emulator, Word operand) {
    andImm8(emulator, ByteValue<R>(emulator));
}

/** Logical OR n with register A, result in A. */
void orImm8(Emulator &emulator, Word operand);

/** Logical OR n with register A, result in A. */
template<ByteArg R>
void orR8(Emulator &emulator, Word operand) {
    orImm8(emulator, ByteValue<R>(emulator));
}

/** Logical exclusive OR register n with register A, result in A. */
void xorImm8(Emulator &emulator, Word operand);

/** Logical exclusive OR register n with register A, result in A. */
template<ByteArg R>
void xorR8(Emulator &emulator, Word operand) {
    xorImm8(emulator, ByteValue<R>(emulator));
}

/**
 * Compare A with n. This is basically an A - n subtraction instruction but
 * the results are thrown away.
 */
template<ByteArg R>
void cp(Emulator &emulator, Word operand) {
    subFlags(emulator, ByteValue<ByteArg::REG_A>(emulator), ByteValue<R>(emulator));
}

/**
 * Compare A with operand. This is basically an A - operand subtraction
 * instruction but the results are thrown away.
 */
void cpImm8(Emulator &emulator, Word operand);

/** Increment single-byte register n. */
template<ByteArg R>
void incR8(Emulator &emulator, Word operand) {
    ByteValue<R> value(emulator);
    Byte oldValue = value;
    ++value;

    emulator.cpu.setFlag(CPUFlags::ZERO, value == 0);
    emulator.cpu.resetFlag(CPUFlags::SUBTRACT);
    emulator.cpu.setFlag(
            CPUFlags::HALF_CARRY, (((oldValue & 0x0F) + 1) & 0xF0) != 0);
}

/** Decrement single-byte register n. */
template<ByteArg R>
void decR8(Emulator &emulator, Word operand) {
    ByteValue<R> value(emulator);
    Byte oldValue = value;
    --value;

    emulator.cpu.setFlag(CPUFlags::ZERO, value == 0);
    emulator.cpu.setFlag(CPUFlags::SUBTRACT);
    emulator.cpu.setFlag(CPUFlags::HALF_CARRY, (oldValue & 0x0F) == 0);
}

// ####################################
// 16-Bit Arithmetic
// ####################################

/** Add n to HL. */
template<WordArg SRC>
void addHlR16(Emulator &emulator, Word operand) {
    Word a = emulator.cpu.registers.hl;
    Word b = WordValue<SRC>(emulator);
    emulator.cpu.registers.hl += b;

    emulator.cpu.resetFlag(CPUFlags::SUBTRACT);
    emulator.cpu.setFlag(
            CPUFlags::CARRY, ((static_cast<uint32_t>(a) + b) & 0xFFFF0000) != 0);
    emulator.cpu.setFlag(
            CPUFlags::HALF_CARRY, (((a & 0x0FFF) + (b & 0x0FFF)) & 0xF000) != 0);
}

/** Add n to Stack Pointer (SP). */
void addSpImm8(Emulator &emulator, Word operand);

/**
 * Perform a + b addition (assuming a is 16-bit and b is a signed 8-bit value),
 * set the flags and return the result. (not an actual instruction)
 *
 * Used in "ADD SP, imm8" and "LD HL, (SP + imm8)".
 */
Word addWordByteFlags(Emulator &emulator, Word a, SignedByte b);

/** Increment double-byte register n. */
template<WordArg R>
void incR16(Emulator &emulator, Word operand) {
    ++WordValue<R>(emulator);
}

/** Decrement double-byte register n. */
template<WordArg R>
void decR16(Emulator &emulator, Word operand) {
    --WordValue<R>(emulator);
}

}
}


#endif //GAMEBOY_EMULATOR_ARITHMETIC_H
