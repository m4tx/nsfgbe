#ifndef GAMEBOY_EMULATOR_INSTRUCTIONDECODER_H
#define GAMEBOY_EMULATOR_INSTRUCTIONDECODER_H


#include <emulator/cpu/CPU.hpp>
#include <emulator/mmu/MMU.hpp>
#include "Instruction.hpp"
#include "InstructionInstance.hpp"

namespace nsfgbe {

class InstructionDecoder {
private:
    CPU &cpu;
    MMU &mmu;

public:
    InstructionDecoder(CPU &cpu, MMU &mmu);

    const Instruction &getInstructionAt(Address address) const;

    InstructionInstance retrieveInstruction();
};

}


#endif //GAMEBOY_EMULATOR_INSTRUCTIONDECODER_H
