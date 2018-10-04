#include <emulator/Constants.hpp>
#include "InstructionDecoder.hpp"
#include "InstructionList.hpp"
#include "ExtendedInstructionList.hpp"

namespace gb {

InstructionDecoder::InstructionDecoder(CPU &cpu, MMU &mmu) :
        cpu(cpu), mmu(mmu) {}

const Instruction &InstructionDecoder::getInstructionAt(Address address) const {
    Byte opcode = mmu[address];

    if (address < 0xFFFF) {
        // Check two-byte opcodes
        if (opcode == 0x10 && mmu[address + 1] == 0x00) {
            return STOP_INSTRUCTION;
        } else if (opcode == 0xCB) {
            // Extended CB instruction
            return EXTENDED_INSTRUCTION_LIST[mmu[address + 1]];
        }
    }

    return INSTRUCTION_LIST[opcode];
}

InstructionInstance InstructionDecoder::retrieveInstruction() {
    Word pc = cpu.registers.pc;
    const Instruction &instruction = getInstructionAt(pc);
    Word newPc = pc + instruction.opcodeLength;

    Word operand = 0;
    switch (instruction.operandLength) {
        case OPERAND_LEN_ONE:
            operand = mmu[newPc];
            break;
        case OPERAND_LEN_TWO:
            operand = mmu[newPc] + (mmu[newPc + 1] << 8);
            break;
        case OPERAND_LEN_ZERO:
            break;
    }
    newPc += instruction.operandLength;

    cpu.registers.pc = newPc;
    return InstructionInstance(pc, instruction, operand);
}

}
