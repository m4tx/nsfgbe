#ifndef GAMEBOY_EMULATOR_INSTRUCTION_H
#define GAMEBOY_EMULATOR_INSTRUCTION_H


#include <string>
#include <functional>

#include <emulator/cpu/CPUTypes.hpp>

namespace nsfgbe {

class Emulator;

enum class OperandLength {
    ZERO = 0,
    ONE = 1,
    TWO = 2,
};

enum class OpcodeLength {
    ONE = 1,
    TWO = 2,
};

typedef std::function<void(Emulator &, Operand)> Executor;

void defaultExecutor(Emulator &emulator, Operand operand);

class Instruction {
public:
    std::string format;
    size_t ticks;
    OperandLength operandLength;
    OpcodeLength opcodeLength;
    Executor executor;

    explicit Instruction(
            std::string format = "",
            size_t ticks = 4,
            Executor executor = defaultExecutor,
            OperandLength operandLength = OperandLength::ZERO,
            OpcodeLength opcodeLength = OpcodeLength::ONE);

    Instruction(Instruction &&other) noexcept;

    Instruction &operator=(const Instruction &other);
};

}


#endif //GAMEBOY_EMULATOR_INSTRUCTION_H
