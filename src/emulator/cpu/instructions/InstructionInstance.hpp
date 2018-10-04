#ifndef GAMEBOY_EMULATOR_INSTRUCTIONINSTANCE_H
#define GAMEBOY_EMULATOR_INSTRUCTIONINSTANCE_H


#include "Instruction.hpp"

#include <ostream>

#include <Types.hpp>

namespace gb {

class InstructionInstance {
public:
    const Address address;
    const Instruction &instruction;
    const Operand operand;

    InstructionInstance(Address address, const Instruction &instruction,
                        Operand operand);

    void execute(Emulator &emulator);

    friend std::ostream &
    operator<<(std::ostream &os, const InstructionInstance &instance);
};

}


#endif //GAMEBOY_EMULATOR_INSTRUCTIONINSTANCE_H
