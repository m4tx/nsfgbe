#ifndef GAMEBOY_EMULATOR_LOADS_H
#define GAMEBOY_EMULATOR_LOADS_H


#include <emulator/Emulator.hpp>
#include <emulator/cpu/instructions/ByteValue.hpp>
#include <emulator/cpu/instructions/WordValue.hpp>

namespace nsfgbe {
namespace instr {

// ####################################
// 8-Bit Loads
// ####################################

/** Put one-byte value n into arg. */
template<InstrArgByte R>
void ldR8Imm8(Emulator &emulator, Word operand) {
    ByteValue<R> dst(emulator);
    dst = static_cast<Byte>(operand);
}

/** Put value src into dst. */
template<InstrArgByte DST, InstrArgByte SRC>
void ldR8R8(Emulator &emulator, Word operand) {
    ByteValue<DST> dst(emulator);
    dst = static_cast<Byte>(ByteValue<SRC>(emulator));
}

/** Put value [nn] into A. */
void ldAPtrImm16(Emulator &emulator, Word operand);

/** Put value A into [nn]. */
void ldPtrImm16A(Emulator &emulator, Word operand);

/** Put value at address $FF00 (I/O ports) + register C into A. */
void ldAIoC(Emulator &emulator, Word operand);

/** Put A into address $FF00 (I/O ports) + register C. */
void ldIoCA(Emulator &emulator, Word operand);

/** Put value at address HL into A. Decrement HL. */
void lddAHl(Emulator &emulator, Word operand);

/** Put A into memory address HL. Decrement HL. */
void lddHlA(Emulator &emulator, Word operand);

/** Put value at address HL into A. Increment HL. */
void ldiAHl(Emulator &emulator, Word operand);

/** Put A into memory address HL. Increment HL. */
void ldiHlA(Emulator &emulator, Word operand);

/** Put A into address $FF00 (I/O ports) + one-byte operand N. */
void ldhIoImm8A(Emulator &emulator, Word operand);

/** Put value at address $FF00 (I/O ports) + one-byte operand N into A. */
void ldhAIoImm8(Emulator &emulator, Word operand);

// ####################################
// 16-Bit Loads
// ####################################

/** Put two-byte value n into arg. */
template<InstrArgWord R>
void ldR16Imm16(Emulator &emulator, Word operand) {
    WordValue<R> dst(emulator);
    dst = operand;
}

/** Put HL into Stack Pointer (SP). */
void ldSpHl(Emulator &emulator, Word operand);

/** Put SP + n effective address into HL. */
void ldHlSpImm8(Emulator &emulator, Word operand);

/** Put Stack Pointer (SP) at address n. */
void lddPtrImm16Sp(Emulator &emulator, Word operand);

/** Push immediate two-byte value on stack. (not an actual instruction) */
void pushImm16(Emulator &emulator, Word operand);

/** Pop and return two bytes off stack. (not an actual instruction) */
Word popRet16(Emulator &emulator);

/** Push register pair nn onto stack. Decrement Stack Pointer (SP) twice. */
template<InstrArgWord R>
void push(Emulator &emulator, Word operand) {
    pushImm16(emulator, WordValue<R>(emulator));
}

/**
 * Pop two bytes off stack into register pair nn. Increment
 * Stack Pointer (SP) twice.
 */
template<InstrArgWord R>
void pop(Emulator &emulator, Word operand) {
    WordValue<R> dst(emulator);
    dst = popRet16(emulator);
}

}
}

#endif //GAMEBOY_EMULATOR_LOADS_H
