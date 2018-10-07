#include <emulator/Constants.hpp>
#include "InstructionDecoder.hpp"
#include "InstructionList.hpp"
#include "ExtendedInstructionList.hpp"

namespace nsfgbe {

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
    Word newPc = pc + static_cast<Word>(instruction.opcodeLength);

    Word operand = 0;
    switch (instruction.operandLength) {
        case OperandLength::ONE:
            operand = mmu[newPc];
            break;
        case OperandLength::TWO:
            operand = mmu[newPc] + (mmu[newPc + 1] << 8);
            break;
        case OperandLength::ZERO:
            break;
    }
    newPc += static_cast<Word>(instruction.operandLength);

    cpu.registers.pc = newPc;
    return InstructionInstance(pc, instruction, operand);
}

}
