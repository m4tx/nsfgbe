#ifndef GAMEBOY_EMULATOR_INSTRUCTIONLIST_H
#define GAMEBOY_EMULATOR_INSTRUCTIONLIST_H


#include <array>

#include "Instruction.hpp"

namespace gb {

extern const std::array<Instruction, 256> INSTRUCTION_LIST;
extern const Instruction STOP_INSTRUCTION;

}


#endif //GAMEBOY_EMULATOR_INSTRUCTIONLIST_H
