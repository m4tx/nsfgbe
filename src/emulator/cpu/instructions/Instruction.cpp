#include "Instruction.hpp"

#include <utility>

namespace nsfgbe {

void defaultExecutor(Emulator &emulator, Operand operand) {
    throw std::runtime_error("Instruction not implemented");
}

Instruction::Instruction(
        std::string format,
        size_t ticks,
        Executor executor,
        OperandLength operandLength,
        OpcodeLength opcodeLength
) :
        format(std::move(format)),
        ticks(ticks),
        executor(std::move(executor)),
        operandLength(operandLength),
        opcodeLength(opcodeLength) {}

Instruction::Instruction(Instruction &&other) noexcept :
        format(other.format),
        ticks(other.ticks),
        executor(other.executor),
        operandLength(other.operandLength),
        opcodeLength(other.opcodeLength) {}

Instruction &Instruction::operator=(const Instruction &other) = default;

}
