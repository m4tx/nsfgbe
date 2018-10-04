#ifndef GAMEBOY_EMULATOR_JUMPS_H
#define GAMEBOY_EMULATOR_JUMPS_H


#include <emulator/Emulator.hpp>

namespace gb {
namespace instr {

/** Jump to address nn. */
void jp(Emulator &emulator, Word operand);

/** Jump to address nn if Z flag is reset. */
void jpNz(Emulator &emulator, Word operand);

/** Jump to address nn if Z flag is set. */
void jpZ(Emulator &emulator, Word operand);

/** Jump to address nn if C flag is reset. */
void jpNc(Emulator &emulator, Word operand);

/** Jump to address nn if C flag is set. */
void jpC(Emulator &emulator, Word operand);

/** Jump to address contained in HL. */
void jpPtrHl(Emulator &emulator, Word operand);

/** Add n to current address and jump to it. */
void jr(Emulator &emulator, Word operand);

/** If Z flag is reset then add n to current address and jump to it. */
void jrNz(Emulator &emulator, Word operand);

/** If Z flag is set then add n to current address and jump to it. */
void jrZ(Emulator &emulator, Word operand);

/** If C flag is reset then add n to current address and jump to it. */
void jrNc(Emulator &emulator, Word operand);

/** If C flag is set then add n to current address and jump to it. */
void jrC(Emulator &emulator, Word operand);

}
}


#endif //GAMEBOY_EMULATOR_JUMPS_H
