#ifndef GAMEBOY_EMULATOR_MISCELLANEOUS_H
#define GAMEBOY_EMULATOR_MISCELLANEOUS_H


#include <emulator/Emulator.hpp>
#include <emulator/cpu/instructions/ByteValue.hpp>

namespace nsfgbe {
namespace instr {

/** Swap upper & lower nibbles of n. */
template <ByteArg R>
void swap(Emulator &emulator, Word operand) {
    ByteValue<R> value(emulator);
    // Byte is actually unsigned char, so no sign-extending occurs in value >> 4
    value = (value >> 4) | (value << 4);

    emulator.cpu.resetFlag(CPUFlags::ALL_FLAGS);
    emulator.cpu.setFlag(CPUFlags::ZERO, value == 0);
}

/** Decimal adjust register A.
 *
 * This instruction adjusts register A so that the correct representation of
 * Binary Coded Decimal (BCD) is obtained.
 */
void daa(Emulator &emulator, Word operand);

/** Complement A register. (Flip all bits.) */
void cpl(Emulator &emulator, Word operand);

/** Complement carry flag. */
void ccf(Emulator &emulator, Word operand);

/** Set Carry flag. */
void scf(Emulator &emulator, Word operand);

/** Do nothing. */
void nop(Emulator &emulator, Word operand);

/** Power down CPU until an interrupt occurs. */
void halt(Emulator &emulator, Word operand);

/**
 * Enable interrupts. This intruction enables interrupts but not immediately.
 * Interrupts are enabled after instruction after EI is executed.
 */
void ei(Emulator &emulator, Word operand);

/**
 * This instruction disables interrupts but not immediately.
 * Interrupts are disabled after instruction after DI is executed.
 */
void di(Emulator &emulator, Word operand);

}
}


#endif //GAMEBOY_EMULATOR_MISCELLANEOUS_H
