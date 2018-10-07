#include "InstructionList.hpp"
#include "InstructionImpl.hpp"

using namespace nsfgbe::instr;

namespace nsfgbe {

const std::array<Instruction, 256> INSTRUCTION_LIST{
        // 0x00
        Instruction("NOP", 4, nop),
        // 0x01
        Instruction("LD BC, %x", 12, ldR16Imm16<WordArg::REG_BC>, OperandLength::TWO),
        // 0x02
        Instruction("LD [BC], A", 8, ldR8R8<ByteArg::PTR_BC, ByteArg::REG_A>),
        // 0x03
        Instruction("INC BC", 8, incR16<WordArg::REG_BC>),
        // 0x04
        Instruction("INC B", 4, incR8<ByteArg::REG_B>),
        // 0x05
        Instruction("DEC B", 4, decR8<ByteArg::REG_B>),
        // 0x06
        Instruction("LD B, %x", 8, ldR8Imm8<ByteArg::REG_B>, OperandLength::ONE),
        // 0x07
        Instruction("RLCA", 4, rlca),
        // 0x08
        Instruction("LD [%x], SP", 20, lddPtrImm16Sp, OperandLength::TWO),
        // 0x09
        Instruction("ADD HL, BC", 8, addHlR16<WordArg::REG_BC>),
        // 0x0A
        Instruction("LD A, [BC]", 8, ldR8R8<ByteArg::REG_A, ByteArg::PTR_BC>),
        // 0x0B
        Instruction("DEC BC", 8, decR16<WordArg::REG_BC>),
        // 0x0C
        Instruction("INC C", 4, incR8<ByteArg::REG_C>),
        // 0x0D
        Instruction("DEC C", 4, decR8<ByteArg::REG_C>),
        // 0x0E
        Instruction("LD C, %x", 8, ldR8Imm8<ByteArg::REG_C>, OperandLength::ONE),
        // 0x0F
        Instruction("RRCA", 4, rrca),
        // 0x10
        Instruction("DB $10", 4),
        // 0x11
        Instruction("LD DE, %x", 12, ldR16Imm16<WordArg::REG_DE>, OperandLength::TWO),
        // 0x12
        Instruction("LD [DE], A", 8, ldR8R8<ByteArg::PTR_DE, ByteArg::REG_A>),
        // 0x13
        Instruction("INC DE", 8, incR16<WordArg::REG_DE>),
        // 0x14
        Instruction("INC D", 4, incR8<ByteArg::REG_D>),
        // 0x15
        Instruction("DEC D", 4, decR8<ByteArg::REG_D>),
        // 0x16
        Instruction("LD D, %x", 8, ldR8Imm8<ByteArg::REG_D>, OperandLength::ONE),
        // 0x17
        Instruction("RLA", 4, rla),
        // 0x18
        Instruction("JR %x", 12, jr, OperandLength::ONE),
        // 0x19
        Instruction("ADD HL, DE", 8, addHlR16<WordArg::REG_DE>),
        // 0x1A
        Instruction("LD A, [DE]", 8, ldR8R8<ByteArg::REG_A, ByteArg::PTR_DE>),
        // 0x1B
        Instruction("DEC DE", 8, decR16<WordArg::REG_DE>),
        // 0x1C
        Instruction("INC E", 4, incR8<ByteArg::REG_E>),
        // 0x1D
        Instruction("DEC E", 4, decR8<ByteArg::REG_E>),
        // 0x1E
        Instruction("LD E, %x", 8, ldR8Imm8<ByteArg::REG_E>, OperandLength::ONE),
        // 0x1F
        Instruction("RRA", 4, rra),
        // 0x20
        // todo 12 cycles
        Instruction("JR NZ, %x", 8, jrNz, OperandLength::ONE),
        // 0x21
        Instruction("LD HL, %x", 12, ldR16Imm16<WordArg::REG_HL>, OperandLength::TWO),
        // 0x22
        Instruction("LDI [HL], A", 8, ldiHlA),
        // 0x23
        Instruction("INC HL", 8, incR16<WordArg::REG_HL>),
        // 0x24
        Instruction("INC H", 4, incR8<ByteArg::REG_H>),
        // 0x25
        Instruction("DEC H", 4, decR8<ByteArg::REG_H>),
        // 0x26
        Instruction("LD H, %x", 8, ldR8Imm8<ByteArg::REG_H>, OperandLength::ONE),
        // 0x27
        Instruction("DAA", 4, daa),
        // 0x28
        // todo 12 cycles
        Instruction("JR Z, %x", 8, jrZ, OperandLength::ONE),
        // 0x29
        Instruction("ADD HL, HL", 8, addHlR16<WordArg::REG_HL>),
        // 0x2A
        Instruction("LDI A, [HL]", 8, ldiAHl),
        // 0x2B
        Instruction("DEC HL", 8, decR16<WordArg::REG_HL>),
        // 0x2C
        Instruction("INC L", 4, incR8<ByteArg::REG_L>),
        // 0x2D
        Instruction("DEC L", 4, decR8<ByteArg::REG_L>),
        // 0x2E
        Instruction("LD L, %x", 8, ldR8Imm8<ByteArg::REG_L>, OperandLength::ONE),
        // 0x2F
        Instruction("CPL", 4, cpl),
        // 0x30
        // todo 12 cycles
        Instruction("JR NC, %x", 8, jrNc, OperandLength::ONE),
        // 0x31
        Instruction("LD SP, %x", 12, ldR16Imm16<WordArg::REG_SP>, OperandLength::TWO),
        // 0x32
        Instruction("LDD [HL], A", 8, lddHlA),
        // 0x33
        Instruction("INC SP", 8, incR16<WordArg::REG_SP>),
        // 0x34
        Instruction("INC [HL]", 12, incR8<ByteArg::PTR_HL>),
        // 0x35
        Instruction("DEC [HL]", 12, decR8<ByteArg::PTR_HL>),
        // 0x36
        Instruction("LD [HL], %x", 12, ldR8Imm8<ByteArg::PTR_HL>, OperandLength::ONE),
        // 0x37
        Instruction("SCF", 4, scf),
        // 0x38
        // todo 12 cycles
        Instruction("JR C, %x", 8, jrC, OperandLength::ONE),
        // 0x39
        Instruction("ADD HL, SP", 8, addHlR16<WordArg::REG_SP>),
        // 0x3A
        Instruction("LDD A, [HL]", 8, lddAHl),
        // 0x3B
        Instruction("DEC SP", 8, decR16<WordArg::REG_SP>),
        // 0x3C
        Instruction("INC A", 4, incR8<ByteArg::REG_A>),
        // 0x3D
        Instruction("DEC A", 4, decR8<ByteArg::REG_A>),
        // 0x3E
        Instruction("LD A, %x", 8, ldR8Imm8<ByteArg::REG_A>, OperandLength::ONE),
        // 0x3F
        Instruction("CCF", 4, ccf),
        // 0x40
        Instruction("LD B, B", 4, ldR8R8<ByteArg::REG_B, ByteArg::REG_B>),
        // 0x41
        Instruction("LD B, C", 4, ldR8R8<ByteArg::REG_B, ByteArg::REG_C>),
        // 0x42
        Instruction("LD B, D", 4, ldR8R8<ByteArg::REG_B, ByteArg::REG_D>),
        // 0x43
        Instruction("LD B, E", 4, ldR8R8<ByteArg::REG_B, ByteArg::REG_E>),
        // 0x44
        Instruction("LD B, H", 4, ldR8R8<ByteArg::REG_B, ByteArg::REG_H>),
        // 0x45
        Instruction("LD B, L", 4, ldR8R8<ByteArg::REG_B, ByteArg::REG_L>),
        // 0x46
        Instruction("LD B, [HL]", 8, ldR8R8<ByteArg::REG_B, ByteArg::PTR_HL>),
        // 0x47
        Instruction("LD B, A", 4, ldR8R8<ByteArg::REG_B, ByteArg::REG_A>),
        // 0x48
        Instruction("LD C, B", 4, ldR8R8<ByteArg::REG_C, ByteArg::REG_B>),
        // 0x49
        Instruction("LD C, C", 4, ldR8R8<ByteArg::REG_C, ByteArg::REG_C>),
        // 0x4A
        Instruction("LD C, D", 4, ldR8R8<ByteArg::REG_C, ByteArg::REG_D>),
        // 0x4B
        Instruction("LD C, E", 4, ldR8R8<ByteArg::REG_C, ByteArg::REG_E>),
        // 0x4C
        Instruction("LD C, H", 4, ldR8R8<ByteArg::REG_C, ByteArg::REG_H>),
        // 0x4D
        Instruction("LD C, L", 4, ldR8R8<ByteArg::REG_C, ByteArg::REG_L>),
        // 0x4E
        Instruction("LD C, [HL]", 8, ldR8R8<ByteArg::REG_C, ByteArg::PTR_HL>),
        // 0x4F
        Instruction("LD C, A", 4, ldR8R8<ByteArg::REG_C, ByteArg::REG_A>),
        // 0x50
        Instruction("LD D, B", 4, ldR8R8<ByteArg::REG_D, ByteArg::REG_B>),
        // 0x51
        Instruction("LD D, C", 4, ldR8R8<ByteArg::REG_D, ByteArg::REG_C>),
        // 0x52
        Instruction("LD D, D", 4, ldR8R8<ByteArg::REG_D, ByteArg::REG_D>),
        // 0x53
        Instruction("LD D, E", 4, ldR8R8<ByteArg::REG_D, ByteArg::REG_E>),
        // 0x54
        Instruction("LD D, H", 4, ldR8R8<ByteArg::REG_D, ByteArg::REG_H>),
        // 0x55
        Instruction("LD D, L", 4, ldR8R8<ByteArg::REG_D, ByteArg::REG_L>),
        // 0x56
        Instruction("LD D, [HL]", 8, ldR8R8<ByteArg::REG_D, ByteArg::PTR_HL>),
        // 0x57
        Instruction("LD D, A", 4, ldR8R8<ByteArg::REG_D, ByteArg::REG_A>),
        // 0x58
        Instruction("LD E, B", 4, ldR8R8<ByteArg::REG_E, ByteArg::REG_B>),
        // 0x59
        Instruction("LD E, C", 4, ldR8R8<ByteArg::REG_E, ByteArg::REG_C>),
        // 0x5A
        Instruction("LD E, D", 4, ldR8R8<ByteArg::REG_E, ByteArg::REG_D>),
        // 0x5B
        Instruction("LD E, E", 4, ldR8R8<ByteArg::REG_E, ByteArg::REG_E>),
        // 0x5C
        Instruction("LD E, H", 4, ldR8R8<ByteArg::REG_E, ByteArg::REG_H>),
        // 0x5D
        Instruction("LD E, L", 4, ldR8R8<ByteArg::REG_E, ByteArg::REG_L>),
        // 0x5E
        Instruction("LD E, [HL]", 8, ldR8R8<ByteArg::REG_E, ByteArg::PTR_HL>),
        // 0x5F
        Instruction("LD E, A", 4, ldR8R8<ByteArg::REG_E, ByteArg::REG_A>),
        // 0x60
        Instruction("LD H, B", 4, ldR8R8<ByteArg::REG_H, ByteArg::REG_B>),
        // 0x61
        Instruction("LD H, C", 4, ldR8R8<ByteArg::REG_H, ByteArg::REG_C>),
        // 0x62
        Instruction("LD H, D", 4, ldR8R8<ByteArg::REG_H, ByteArg::REG_D>),
        // 0x63
        Instruction("LD H, E", 4, ldR8R8<ByteArg::REG_H, ByteArg::REG_E>),
        // 0x64
        Instruction("LD H, H", 4, ldR8R8<ByteArg::REG_H, ByteArg::REG_H>),
        // 0x65
        Instruction("LD H, L", 4, ldR8R8<ByteArg::REG_H, ByteArg::REG_L>),
        // 0x66
        Instruction("LD H, [HL]", 8, ldR8R8<ByteArg::REG_H, ByteArg::PTR_HL>),
        // 0x67
        Instruction("LD H, A", 4, ldR8R8<ByteArg::REG_H, ByteArg::REG_A>),
        // 0x68
        Instruction("LD L, B", 4, ldR8R8<ByteArg::REG_L, ByteArg::REG_B>),
        // 0x69
        Instruction("LD L, C", 4, ldR8R8<ByteArg::REG_L, ByteArg::REG_C>),
        // 0x6A
        Instruction("LD L, D", 4, ldR8R8<ByteArg::REG_L, ByteArg::REG_D>),
        // 0x6B
        Instruction("LD L, E", 4, ldR8R8<ByteArg::REG_L, ByteArg::REG_E>),
        // 0x6C
        Instruction("LD L, H", 4, ldR8R8<ByteArg::REG_L, ByteArg::REG_H>),
        // 0x6D
        Instruction("LD L, L", 4, ldR8R8<ByteArg::REG_L, ByteArg::REG_L>),
        // 0x6E
        Instruction("LD L, [HL]", 8, ldR8R8<ByteArg::REG_L, ByteArg::PTR_HL>),
        // 0x6F
        Instruction("LD L, A", 4, ldR8R8<ByteArg::REG_L, ByteArg::REG_A>),
        // 0x70
        Instruction("LD [HL], B", 8, ldR8R8<ByteArg::PTR_HL, ByteArg::REG_B>),
        // 0x71
        Instruction("LD [HL], C", 8, ldR8R8<ByteArg::PTR_HL, ByteArg::REG_C>),
        // 0x72
        Instruction("LD [HL], D", 8, ldR8R8<ByteArg::PTR_HL, ByteArg::REG_D>),
        // 0x73
        Instruction("LD [HL], E", 8, ldR8R8<ByteArg::PTR_HL, ByteArg::REG_E>),
        // 0x74
        Instruction("LD [HL], H", 8, ldR8R8<ByteArg::PTR_HL, ByteArg::REG_H>),
        // 0x75
        Instruction("LD [HL], L", 8, ldR8R8<ByteArg::PTR_HL, ByteArg::REG_L>),
        // 0x76
        Instruction("HALT", 4, halt),
        // 0x77
        Instruction("LD [HL], A", 8, ldR8R8<ByteArg::PTR_HL, ByteArg::REG_A>),
        // 0x78
        Instruction("LD A, B", 4, ldR8R8<ByteArg::REG_A, ByteArg::REG_B>),
        // 0x79
        Instruction("LD A, C", 4, ldR8R8<ByteArg::REG_A, ByteArg::REG_C>),
        // 0x7A
        Instruction("LD A, D", 4, ldR8R8<ByteArg::REG_A, ByteArg::REG_D>),
        // 0x7B
        Instruction("LD A, E", 4, ldR8R8<ByteArg::REG_A, ByteArg::REG_E>),
        // 0x7C
        Instruction("LD A, H", 4, ldR8R8<ByteArg::REG_A, ByteArg::REG_H>),
        // 0x7D
        Instruction("LD A, L", 4, ldR8R8<ByteArg::REG_A, ByteArg::REG_L>),
        // 0x7E
        Instruction("LD A, [HL]", 8, ldR8R8<ByteArg::REG_A, ByteArg::PTR_HL>),
        // 0x7F
        Instruction("LD A, A", 4, ldR8R8<ByteArg::REG_A, ByteArg::REG_A>),
        // 0x80
        Instruction("ADD A, B", 4, add<ByteArg::REG_B>),
        // 0x81
        Instruction("ADD A, C", 4, add<ByteArg::REG_C>),
        // 0x82
        Instruction("ADD A, D", 4, add<ByteArg::REG_D>),
        // 0x83
        Instruction("ADD A, E", 4, add<ByteArg::REG_E>),
        // 0x84
        Instruction("ADD A, H", 4, add<ByteArg::REG_H>),
        // 0x85
        Instruction("ADD A, L", 4, add<ByteArg::REG_L>),
        // 0x86
        Instruction("ADD A, [HL]", 8, add<ByteArg::PTR_HL>),
        // 0x87
        Instruction("ADD A, A", 4, add<ByteArg::REG_A>),
        // 0x88
        Instruction("ADC A, B", 4, adc<ByteArg::REG_B>),
        // 0x89
        Instruction("ADC A, C", 4, adc<ByteArg::REG_C>),
        // 0x8A
        Instruction("ADC A, D", 4, adc<ByteArg::REG_D>),
        // 0x8B
        Instruction("ADC A, E", 4, adc<ByteArg::REG_E>),
        // 0x8C
        Instruction("ADC A, H", 4, adc<ByteArg::REG_H>),
        // 0x8D
        Instruction("ADC A, L", 4, adc<ByteArg::REG_L>),
        // 0x8E
        Instruction("ADC A, [HL]", 8, adc<ByteArg::PTR_HL>),
        // 0x8F
        Instruction("ADC A, A", 4, adc<ByteArg::REG_A>),
        // 0x90
        Instruction("SUB B", 4, sub<ByteArg::REG_B>),
        // 0x91
        Instruction("SUB C", 4, sub<ByteArg::REG_C>),
        // 0x92
        Instruction("SUB D", 4, sub<ByteArg::REG_D>),
        // 0x93
        Instruction("SUB E", 4, sub<ByteArg::REG_E>),
        // 0x94
        Instruction("SUB H", 4, sub<ByteArg::REG_H>),
        // 0x95
        Instruction("SUB L", 4, sub<ByteArg::REG_L>),
        // 0x96
        Instruction("SUB [HL]", 8, sub<ByteArg::PTR_HL>),
        // 0x97
        Instruction("SUB A", 4, sub<ByteArg::REG_A>),
        // 0x98
        Instruction("SBC A, B", 4, sbc<ByteArg::REG_B>),
        // 0x99
        Instruction("SBC A, C", 4, sbc<ByteArg::REG_C>),
        // 0x9A
        Instruction("SBC A, D", 4, sbc<ByteArg::REG_D>),
        // 0x9B
        Instruction("SBC A, E", 4, sbc<ByteArg::REG_E>),
        // 0x9C
        Instruction("SBC A, H", 4, sbc<ByteArg::REG_H>),
        // 0x9D
        Instruction("SBC A, L", 4, sbc<ByteArg::REG_L>),
        // 0x9E
        Instruction("SBC A, [HL]", 8, sbc<ByteArg::PTR_HL>),
        // 0x9F
        Instruction("SBC A, A", 4, sbc<ByteArg::REG_A>),
        // 0xA0
        Instruction("AND B", 4, andR8<ByteArg::REG_B>),
        // 0xA1
        Instruction("AND C", 4, andR8<ByteArg::REG_C>),
        // 0xA2
        Instruction("AND D", 4, andR8<ByteArg::REG_D>),
        // 0xA3
        Instruction("AND E", 4, andR8<ByteArg::REG_E>),
        // 0xA4
        Instruction("AND H", 4, andR8<ByteArg::REG_H>),
        // 0xA5
        Instruction("AND L", 4, andR8<ByteArg::REG_L>),
        // 0xA6
        Instruction("AND [HL]", 8, andR8<ByteArg::PTR_HL>),
        // 0xA7
        Instruction("AND A", 4, andR8<ByteArg::REG_A>),
        // 0xA8
        Instruction("XOR B", 4, xorR8<ByteArg::REG_B>),
        // 0xA9
        Instruction("XOR C", 4, xorR8<ByteArg::REG_C>),
        // 0xAA
        Instruction("XOR D", 4, xorR8<ByteArg::REG_D>),
        // 0xAB
        Instruction("XOR E", 4, xorR8<ByteArg::REG_E>),
        // 0xAC
        Instruction("XOR H", 4, xorR8<ByteArg::REG_H>),
        // 0xAD
        Instruction("XOR L", 4, xorR8<ByteArg::REG_L>),
        // 0xAE
        Instruction("XOR [HL]", 8, xorR8<ByteArg::PTR_HL>),
        // 0xAF
        Instruction("XOR A", 4, xorR8<ByteArg::REG_A>),
        // 0xB0
        Instruction("OR B", 4, orR8<ByteArg::REG_B>),
        // 0xB1
        Instruction("OR C", 4, orR8<ByteArg::REG_C>),
        // 0xB2
        Instruction("OR D", 4, orR8<ByteArg::REG_D>),
        // 0xB3
        Instruction("OR E", 4, orR8<ByteArg::REG_E>),
        // 0xB4
        Instruction("OR H", 4, orR8<ByteArg::REG_H>),
        // 0xB5
        Instruction("OR L", 4, orR8<ByteArg::REG_L>),
        // 0xB6
        Instruction("OR [HL]", 8, orR8<ByteArg::PTR_HL>),
        // 0xB7
        Instruction("OR A", 4, orR8<ByteArg::REG_A>),
        // 0xB8
        Instruction("CP B", 4, cp<ByteArg::REG_B>),
        // 0xB9
        Instruction("CP C", 4, cp<ByteArg::REG_C>),
        // 0xBA
        Instruction("CP D", 4, cp<ByteArg::REG_D>),
        // 0xBB
        Instruction("CP E", 4, cp<ByteArg::REG_E>),
        // 0xBC
        Instruction("CP H", 4, cp<ByteArg::REG_H>),
        // 0xBD
        Instruction("CP L", 4, cp<ByteArg::REG_L>),
        // 0xBE
        Instruction("CP [HL]", 8, cp<ByteArg::PTR_HL>),
        // 0xBF
        Instruction("CP A", 4, cp<ByteArg::REG_A>),
        // 0xC0
        // todo 20 cycles
        Instruction("RET NZ", 8, retNz),
        // 0xC1
        Instruction("POP BC", 12, pop<WordArg::REG_BC>),
        // 0xC2
        // todo 16 cycles
        Instruction("JP NZ, %x", 12, jpNz, OperandLength::TWO),
        // 0xC3
        Instruction("JP %x", 16, jp, OperandLength::TWO),
        // 0xC4
        // todo 24 cycles
        Instruction("CALL NZ, %x", 12, callNzImm16, OperandLength::TWO),
        // 0xC5
        Instruction("PUSH BC", 16, push<WordArg::REG_BC>),
        // 0xC6
        Instruction("ADD A, %x", 8, addImm8, OperandLength::ONE),
        // 0xC7
        Instruction("RST $00", 16, rst<0x00>),
        // 0xC8
        // todo 20 cycles
        Instruction("RET Z", 8, retZ),
        // 0xC9
        Instruction("RET", 16, ret),
        // 0xCA
        // todo 16 cycles
        Instruction("JP Z, %x", 12, jpZ, OperandLength::TWO),
        // 0xCB
        Instruction("DB $CB", 4),
        // 0xCC
        // todo 24 cycles
        Instruction("CALL Z, %x", 12, callZImm16, OperandLength::TWO),
        // 0xCD
        Instruction("CALL %x", 24, callImm16, OperandLength::TWO),
        // 0xCE
        Instruction("ADC A, %x", 8, adcImm8, OperandLength::ONE),
        // 0xCF
        Instruction("RST $08", 16, rst<0x08>),
        // 0xD0
        // todo 20 cycles
        Instruction("RET NC", 8, retNc),
        // 0xD1
        Instruction("POP DE", 12, pop<WordArg::REG_DE>),
        // 0xD2
        // todo 16 cycles
        Instruction("JP NC, %x", 12, jpNc, OperandLength::TWO),
        // 0xD3
        Instruction("DB $D3", 4),
        // 0xD4
        // todo 24 cycles
        Instruction("CALL NC, %x", 12, callNcImm16, OperandLength::TWO),
        // 0xD5
        Instruction("PUSH DE", 16, push<WordArg::REG_DE>),
        // 0xD6
        Instruction("SUB %x", 8, subImm8, OperandLength::ONE),
        // 0xD7
        Instruction("RST $10", 16, rst<0x10>),
        // 0xD8
        // todo 20 cycles
        Instruction("RET C", 8, retC),
        // 0xD9
        Instruction("RETI", 16, reti),
        // 0xDA
        // todo 16 cycles
        Instruction("JP C, %x", 12, jpC, OperandLength::TWO),
        // 0xDB
        Instruction("DB $DB", 4),
        // 0xDC
        // todo 24 cycles
        Instruction("CALL C, %x", 12, callCImm16, OperandLength::TWO),
        // 0xDD
        Instruction("DB $DD", 4),
        // 0xDE
        Instruction("SBC A, %x", 8, sbcImm8, OperandLength::ONE),
        // 0xDF
        Instruction("RST $18", 16, rst<0x18>),
        // 0xE0
        Instruction("LDH ($FF00 + %x), A", 12, ldhIoImm8A, OperandLength::ONE),
        // 0xE1
        Instruction("POP HL", 12, pop<WordArg::REG_HL>),
        // 0xE2
        Instruction("LD ($FF00 + C), A", 8, ldIoCA),
        // 0xE3
        Instruction("DB $E3", 4),
        // 0xE4
        Instruction("DB $E4", 4),
        // 0xE5
        Instruction("PUSH HL", 16, push<WordArg::REG_HL>),
        // 0xE6
        Instruction("AND %x", 8, andImm8, OperandLength::ONE),
        // 0xE7
        Instruction("RST $20", 16, rst<0x20>),
        // 0xE8
        Instruction("ADD SP, %x", 16, addSpImm8, OperandLength::ONE),
        // 0xE9
        Instruction("JP [HL]", 4, jpPtrHl),
        // 0xEA
        Instruction("LD [%x], A", 16, ldPtrImm16A, OperandLength::TWO),
        // 0xEB
        Instruction("DB $EB", 4),
        // 0xEC
        Instruction("DB $EC", 4),
        // 0xED
        Instruction("DB $ED", 4),
        // 0xEE
        Instruction("XOR %x", 8, xorImm8, OperandLength::ONE),
        // 0xEF
        Instruction("RST $28", 16, rst<0x28>),
        // 0xF0
        Instruction("LDH A, ($FF00 + %x)", 12, ldhAIoImm8, OperandLength::ONE),
        // 0xF1
        Instruction("POP AF", 12, pop<WordArg::REG_AF>),
        // 0xF2
        Instruction("LD A, ($FF00 + C)", 8, ldAIoC),
        // 0xF3
        Instruction("DI", 4, di),
        // 0xF4
        Instruction("DB $F4", 4),
        // 0xF5
        Instruction("PUSH AF", 16, push<WordArg::REG_AF>),
        // 0xF6
        Instruction("OR %x", 8, orImm8, OperandLength::ONE),
        // 0xF7
        Instruction("RST $30", 16, rst<0x30>),
        // 0xF8
        Instruction("LD HL, SP + %x", 12, ldHlSpImm8, OperandLength::ONE),
        // 0xF9
        Instruction("LD SP, HL", 8, ldSpHl),
        // 0xFA
        Instruction("LD A, [%x]", 16, ldAPtrImm16, OperandLength::TWO),
        // 0xFB
        Instruction("EI", 4, ei),
        // 0xFC
        Instruction("DB $FC", 4),
        // 0xFD
        Instruction("DB $FD", 4),
        // 0xFE
        Instruction("CP %x", 8, cpImm8, OperandLength::ONE),
        // 0xFF
        Instruction("RST $38", 16, rst<0x38>),
};

const Instruction STOP_INSTRUCTION(
        "STOP", 4, defaultExecutor, OperandLength::ZERO, OpcodeLength::TWO);

}
