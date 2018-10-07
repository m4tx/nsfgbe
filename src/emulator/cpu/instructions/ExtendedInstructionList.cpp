#include "ExtendedInstructionList.hpp"
#include "InstructionImpl.hpp"
#include "impl/Miscellaneous.hpp"


namespace nsfgbe {

using namespace std::string_literals;
using namespace nsfgbe::instr;

#define GEN_INSTRUCTION_VARIANTS(name, executor) \
    Instruction(name " B", 8, executor<ByteArg::REG_B>, \
            OperandLength::ZERO, OpcodeLength::TWO), \
    Instruction(name " C", 8, executor<ByteArg::REG_C>, \
            OperandLength::ZERO, OpcodeLength::TWO), \
    Instruction(name " D", 8, executor<ByteArg::REG_D>, \
            OperandLength::ZERO, OpcodeLength::TWO), \
    Instruction(name " E", 8, executor<ByteArg::REG_E>, \
            OperandLength::ZERO, OpcodeLength::TWO), \
    Instruction(name " H", 8, executor<ByteArg::REG_H>, \
            OperandLength::ZERO, OpcodeLength::TWO), \
    Instruction(name " L", 8, executor<ByteArg::REG_L>, \
            OperandLength::ZERO, OpcodeLength::TWO), \
    Instruction(name " [HL]", 16, executor<ByteArg::PTR_HL>, \
            OperandLength::ZERO, OpcodeLength::TWO), \
    Instruction(name " A", 8, executor<ByteArg::REG_A>, \
            OperandLength::ZERO, OpcodeLength::TWO)

#define GEN_BIT_INSTRUCTION_VARIANTS(name, executor, bit, bitStr, hlPtrTicks) \
    Instruction(name " " bitStr ", B", 8, executor<bit, ByteArg::REG_B>, \
            OperandLength::ZERO, OpcodeLength::TWO), \
    Instruction(name " " bitStr ", C", 8, executor<bit, ByteArg::REG_C>, \
            OperandLength::ZERO, OpcodeLength::TWO), \
    Instruction(name " " bitStr ", D", 8, executor<bit, ByteArg::REG_D>, \
            OperandLength::ZERO, OpcodeLength::TWO), \
    Instruction(name " " bitStr ", E", 8, executor<bit, ByteArg::REG_E>, \
            OperandLength::ZERO, OpcodeLength::TWO), \
    Instruction(name " " bitStr ", H", 8, executor<bit, ByteArg::REG_H>, \
            OperandLength::ZERO, OpcodeLength::TWO), \
    Instruction(name " " bitStr ", L", 8, executor<bit, ByteArg::REG_L>, \
            OperandLength::ZERO, OpcodeLength::TWO), \
    Instruction(name " " bitStr ", [HL]", hlPtrTicks, \
            executor<bit, ByteArg::PTR_HL>, OperandLength::ZERO, OpcodeLength::TWO), \
    Instruction(name " " bitStr ", A", 8, executor<bit, ByteArg::REG_A>, \
            OperandLength::ZERO, OpcodeLength::TWO)

#define GEN_BIT_INSTRUCTION_VARIANTS_8(name, executor, hlPtrTicks) \
    GEN_BIT_INSTRUCTION_VARIANTS(name, executor, 0, "0", hlPtrTicks), \
    GEN_BIT_INSTRUCTION_VARIANTS(name, executor, 1, "1", hlPtrTicks), \
    GEN_BIT_INSTRUCTION_VARIANTS(name, executor, 2, "2", hlPtrTicks), \
    GEN_BIT_INSTRUCTION_VARIANTS(name, executor, 3, "3", hlPtrTicks), \
    GEN_BIT_INSTRUCTION_VARIANTS(name, executor, 4, "4", hlPtrTicks), \
    GEN_BIT_INSTRUCTION_VARIANTS(name, executor, 5, "5", hlPtrTicks), \
    GEN_BIT_INSTRUCTION_VARIANTS(name, executor, 6, "6", hlPtrTicks), \
    GEN_BIT_INSTRUCTION_VARIANTS(name, executor, 7, "7", hlPtrTicks)

const std::array<Instruction, 256> EXTENDED_INSTRUCTION_LIST{
        // 0x00 - 0x07
        GEN_INSTRUCTION_VARIANTS("RLC", rlc),
        // 0x08 - 0x0F
        GEN_INSTRUCTION_VARIANTS("RRC", rrc),
        // 0x10 - 0x17
        GEN_INSTRUCTION_VARIANTS("RL", rl),
        // 0x18 - 0x1F
        GEN_INSTRUCTION_VARIANTS("RR", rr),
        // 0x20 - 0x27
        GEN_INSTRUCTION_VARIANTS("SLA", sla),
        // 0x28 - 0x2F
        GEN_INSTRUCTION_VARIANTS("SRA", sra),
        // 0x30 - 0x37
        GEN_INSTRUCTION_VARIANTS("SWAP", swap),
        // 0x38 - 0x3F
        GEN_INSTRUCTION_VARIANTS("SRL", srl),
        // 0x40 - 0x7F
        GEN_BIT_INSTRUCTION_VARIANTS_8("BIT", bit, 12),
        // 0x80 - 0xBF
        GEN_BIT_INSTRUCTION_VARIANTS_8("RES", res, 16),
        // 0xC0 - 0xFF
        GEN_BIT_INSTRUCTION_VARIANTS_8("SET", set, 16),
};

}
