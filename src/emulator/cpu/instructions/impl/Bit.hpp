#ifndef GAMEBOY_EMULATOR_BIT_H
#define GAMEBOY_EMULATOR_BIT_H


#include <emulator/Emulator.hpp>
#include <emulator/cpu/instructions/ByteValue.hpp>

namespace nsfgbe {
namespace instr {

template<int B, ByteArg R>
void bit(Emulator &emulator, Word operand) {
    Byte value = ByteValue<R>(emulator);

    emulator.cpu.setFlag(CPUFlags::ZERO, (value & (1 << B)) == 0);
    emulator.cpu.resetFlag(CPUFlags::SUBTRACT);
    emulator.cpu.setFlag(CPUFlags::HALF_CARRY);
}

template<int B, ByteArg R>
void res(Emulator &emulator, Word operand) {
    ByteValue<R> value(emulator);
    value &= (Byte) ~(1 << B);
}

template<int B, ByteArg R>
void set(Emulator &emulator, Word operand) {
    ByteValue<R> value(emulator);
    value |= (Byte) (1 << B);
}

}
}


#endif //GAMEBOY_EMULATOR_BIT_H
