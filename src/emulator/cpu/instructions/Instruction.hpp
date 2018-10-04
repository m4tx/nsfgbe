#ifndef GAMEBOY_EMULATOR_INSTRUCTION_H
#define GAMEBOY_EMULATOR_INSTRUCTION_H


#include <string>
#include <functional>

#include <emulator/cpu/CPUTypes.hpp>

namespace nsfgbe {

class Emulator;

enum OperandLength {
    OPERAND_LEN_ZERO = 0,
    OPERAND_LEN_ONE = 1,
    OPERAND_LEN_TWO = 2,
};

enum OpcodeLength {
    OPCODE_LEN_ONE = 1,
    OPCODE_LEN_TWO = 2,
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
            OperandLength operandLength = OPERAND_LEN_ZERO,
            OpcodeLength opcodeLength = OPCODE_LEN_ONE);

    Instruction(Instruction &&other) noexcept;

    Instruction &operator=(const Instruction &other);
};

}


#endif //GAMEBOY_EMULATOR_INSTRUCTION_H
