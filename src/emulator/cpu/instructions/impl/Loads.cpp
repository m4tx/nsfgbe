#include "Loads.hpp"
#include "Arithmetic.hpp"

namespace nsfgbe {
namespace instr {

void ldAPtrImm16(Emulator &emulator, Word operand) {
    emulator.cpu.registers.a = emulator.mmu[operand];
}

void ldPtrImm16A(Emulator &emulator, Word operand) {
    emulator.mmu[operand] = emulator.cpu.registers.a;
}

void ldAIoC(Emulator &emulator, Word operand) {
    emulator.cpu.registers.a = emulator.mmu[0xFF00 + emulator.cpu.registers.c];
}

void ldIoCA(Emulator &emulator, Word operand) {
    emulator.mmu[0xFF00 + emulator.cpu.registers.c] = emulator.cpu.registers.a;
}

void lddAHl(Emulator &emulator, Word operand) {
    emulator.cpu.registers.a = emulator.mmu[emulator.cpu.registers.hl--];
}

void lddHlA(Emulator &emulator, Word operand) {
    emulator.mmu[emulator.cpu.registers.hl--] = emulator.cpu.registers.a;
}

void ldiAHl(Emulator &emulator, Word operand) {
    emulator.cpu.registers.a = emulator.mmu[emulator.cpu.registers.hl++];
}

void ldiHlA(Emulator &emulator, Word operand) {
    emulator.mmu[emulator.cpu.registers.hl++] = emulator.cpu.registers.a;
}

void ldhIoImm8A(Emulator &emulator, Word operand) {
    emulator.mmu[0xFF00 + operand] = emulator.cpu.registers.a;
}

void ldhAIoImm8(Emulator &emulator, Word operand) {
    emulator.cpu.registers.a = emulator.mmu[0xFF00 + operand];
}

void ldSpHl(Emulator &emulator, Word operand) {
    emulator.cpu.registers.sp = emulator.cpu.registers.hl;
}

void ldHlSpImm8(Emulator &emulator, Word operand) {
    emulator.cpu.registers.hl = addWordByteFlags(
            emulator,
            emulator.cpu.registers.sp,
            static_cast<SignedByte>(operand));
}

void lddPtrImm16Sp(Emulator &emulator, Word operand) {
    emulator.mmu.setWord(operand, emulator.cpu.registers.sp);
}

void pushImm16(Emulator &emulator, Word operand) {
    emulator.cpu.registers.sp -= 2;
    emulator.mmu.setWord(emulator.cpu.registers.sp, operand);
}

Word popRet16(Emulator &emulator) {
    Word value = emulator.mmu.getWord(emulator.cpu.registers.sp);
    emulator.cpu.registers.sp += 2;
    return value;
}

}
}
