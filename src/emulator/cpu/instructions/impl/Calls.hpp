#ifndef GAMEBOY_EMULATOR_CALLS_H
#define GAMEBOY_EMULATOR_CALLS_H


#include <emulator/Emulator.hpp>
#include "Loads.hpp"

namespace gb {
namespace instr {

/** Push address of next instruction onto stack and then jump to address nn. */
void callImm16(Emulator &emulator, Word operand);

/** Call address n if Z flag is reset. */
void callNzImm16(Emulator &emulator, Word operand);

/** Call address n if Z flag is set. */
void callZImm16(Emulator &emulator, Word operand);

/** Call address n if C flag is reset. */
void callNcImm16(Emulator &emulator, Word operand);

/** Call address n if C flag is set. */
void callCImm16(Emulator &emulator, Word operand);

/** Push present address onto stack. Jump to address $0000 + n. */
template<Address A>
void rst(Emulator &emulator, Word operand) {
    callImm16(emulator, A);
}

/** Pop two bytes from stack & jump to that address. */
void ret(Emulator &emulator, Word operand);

/** Return if Z flag is reset. */
void retNz(Emulator &emulator, Word operand);

/** Return if Z flag is set. */
void retZ(Emulator &emulator, Word operand);

/** Return if C flag is reset. */
void retNc(Emulator &emulator, Word operand);

/** Return if C flag is set. */
void retC(Emulator &emulator, Word operand);

/** Return then enable interrupts. */
void reti(Emulator &emulator, Word operand);

}
}


#endif //GAMEBOY_EMULATOR_CALLS_H
