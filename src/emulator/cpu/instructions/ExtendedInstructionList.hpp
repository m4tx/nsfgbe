#ifndef GAMEBOY_EMULATOR_EXTENDEDINSTRUCTIONLIST_H
#define GAMEBOY_EMULATOR_EXTENDEDINSTRUCTIONLIST_H


#include <array>

#include "Instruction.hpp"

namespace nsfgbe {

extern const std::array<Instruction, 256> EXTENDED_INSTRUCTION_LIST;

}


#endif //GAMEBOY_EMULATOR_EXTENDEDINSTRUCTIONLIST_H
