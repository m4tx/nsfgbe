#include "ByteValue.hpp"

namespace gb {

template<>
ByteValue<ARG_REG_B>::operator Byte() const {
    return emulator.cpu.registers.b;
}

template<>
ByteValue<ARG_REG_B> &ByteValue<ARG_REG_B>::operator=(Byte value) {
    emulator.cpu.registers.b = value;
    return *this;
}

template<>
ByteValue<ARG_REG_C>::operator Byte() const {
    return emulator.cpu.registers.c;
}

template<>
ByteValue<ARG_REG_C> &ByteValue<ARG_REG_C>::operator=(Byte value) {
    emulator.cpu.registers.c = value;
    return *this;
}

template<>
ByteValue<ARG_REG_D>::operator Byte() const {
    return emulator.cpu.registers.d;
}

template<>
ByteValue<ARG_REG_D> &ByteValue<ARG_REG_D>::operator=(Byte value) {
    emulator.cpu.registers.d = value;
    return *this;
}

template<>
ByteValue<ARG_REG_E>::operator Byte() const {
    return emulator.cpu.registers.e;
}

template<>
ByteValue<ARG_REG_E> &ByteValue<ARG_REG_E>::operator=(Byte value) {
    emulator.cpu.registers.e = value;
    return *this;
}

template<>
ByteValue<ARG_REG_H>::operator Byte() const {
    return emulator.cpu.registers.h;
}

template<>
ByteValue<ARG_REG_H> &ByteValue<ARG_REG_H>::operator=(Byte value) {
    emulator.cpu.registers.h = value;
    return *this;
}

template<>
ByteValue<ARG_REG_L>::operator Byte() const {
    return emulator.cpu.registers.l;
}

template<>
ByteValue<ARG_REG_L> &ByteValue<ARG_REG_L>::operator=(Byte value) {
    emulator.cpu.registers.l = value;
    return *this;
}

template<>
ByteValue<ARG_PTR_HL>::operator Byte() const {
    return emulator.mmu[emulator.cpu.registers.hl];
}

template<>
ByteValue<ARG_PTR_HL> &ByteValue<ARG_PTR_HL>::operator=(Byte value) {
    emulator.mmu[emulator.cpu.registers.hl] = value;
    return *this;
}

template<>
ByteValue<ARG_REG_A>::operator Byte() const {
    return emulator.cpu.registers.a;
}

template<>
ByteValue<ARG_REG_A> &ByteValue<ARG_REG_A>::operator=(Byte value) {
    emulator.cpu.registers.a = value;
    return *this;
}

template<>
ByteValue<ARG_PTR_BC>::operator Byte() const {
    return emulator.mmu[emulator.cpu.registers.bc];
}

template<>
ByteValue<ARG_PTR_BC> &ByteValue<ARG_PTR_BC>::operator=(Byte value) {
    emulator.mmu[emulator.cpu.registers.bc] = value;
    return *this;
}

template<>
ByteValue<ARG_PTR_DE>::operator Byte() const {
    return emulator.mmu[emulator.cpu.registers.de];
}

template<>
ByteValue<ARG_PTR_DE> &ByteValue<ARG_PTR_DE>::operator=(Byte value) {
    emulator.mmu[emulator.cpu.registers.de] = value;
    return *this;
}

}
