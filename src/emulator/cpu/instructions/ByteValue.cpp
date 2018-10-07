#include "ByteValue.hpp"

namespace nsfgbe {

template<>
ByteValue<ByteArg::REG_B>::operator Byte() const {
    return emulator.cpu.registers.b;
}

template<>
ByteValue<ByteArg::REG_B> &ByteValue<ByteArg::REG_B>::operator=(Byte value) {
    emulator.cpu.registers.b = value;
    return *this;
}

template<>
ByteValue<ByteArg::REG_C>::operator Byte() const {
    return emulator.cpu.registers.c;
}

template<>
ByteValue<ByteArg::REG_C> &ByteValue<ByteArg::REG_C>::operator=(Byte value) {
    emulator.cpu.registers.c = value;
    return *this;
}

template<>
ByteValue<ByteArg::REG_D>::operator Byte() const {
    return emulator.cpu.registers.d;
}

template<>
ByteValue<ByteArg::REG_D> &ByteValue<ByteArg::REG_D>::operator=(Byte value) {
    emulator.cpu.registers.d = value;
    return *this;
}

template<>
ByteValue<ByteArg::REG_E>::operator Byte() const {
    return emulator.cpu.registers.e;
}

template<>
ByteValue<ByteArg::REG_E> &ByteValue<ByteArg::REG_E>::operator=(Byte value) {
    emulator.cpu.registers.e = value;
    return *this;
}

template<>
ByteValue<ByteArg::REG_H>::operator Byte() const {
    return emulator.cpu.registers.h;
}

template<>
ByteValue<ByteArg::REG_H> &ByteValue<ByteArg::REG_H>::operator=(Byte value) {
    emulator.cpu.registers.h = value;
    return *this;
}

template<>
ByteValue<ByteArg::REG_L>::operator Byte() const {
    return emulator.cpu.registers.l;
}

template<>
ByteValue<ByteArg::REG_L> &ByteValue<ByteArg::REG_L>::operator=(Byte value) {
    emulator.cpu.registers.l = value;
    return *this;
}

template<>
ByteValue<ByteArg::PTR_HL>::operator Byte() const {
    return emulator.mmu[emulator.cpu.registers.hl];
}

template<>
ByteValue<ByteArg::PTR_HL> &ByteValue<ByteArg::PTR_HL>::operator=(Byte value) {
    emulator.mmu[emulator.cpu.registers.hl] = value;
    return *this;
}

template<>
ByteValue<ByteArg::REG_A>::operator Byte() const {
    return emulator.cpu.registers.a;
}

template<>
ByteValue<ByteArg::REG_A> &ByteValue<ByteArg::REG_A>::operator=(Byte value) {
    emulator.cpu.registers.a = value;
    return *this;
}

template<>
ByteValue<ByteArg::PTR_BC>::operator Byte() const {
    return emulator.mmu[emulator.cpu.registers.bc];
}

template<>
ByteValue<ByteArg::PTR_BC> &ByteValue<ByteArg::PTR_BC>::operator=(Byte value) {
    emulator.mmu[emulator.cpu.registers.bc] = value;
    return *this;
}

template<>
ByteValue<ByteArg::PTR_DE>::operator Byte() const {
    return emulator.mmu[emulator.cpu.registers.de];
}

template<>
ByteValue<ByteArg::PTR_DE> &ByteValue<ByteArg::PTR_DE>::operator=(Byte value) {
    emulator.mmu[emulator.cpu.registers.de] = value;
    return *this;
}

}
