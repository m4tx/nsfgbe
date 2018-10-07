#include "WordValue.hpp"

namespace nsfgbe {

template<>
WordValue<WordArg::REG_AF>::operator Word() const {
    return emulator.cpu.registers.af & 0xFFF0_w;
}

template<>
WordValue<WordArg::REG_AF> &WordValue<WordArg::REG_AF>::operator=(Word value) {
    emulator.cpu.registers.af = value & 0xFFF0_w;
    return *this;
}


template<>
WordValue<WordArg::REG_BC>::operator Word() const {
    return emulator.cpu.registers.bc;
}

template<>
WordValue<WordArg::REG_BC> &WordValue<WordArg::REG_BC>::operator=(Word value) {
    emulator.cpu.registers.bc = value;
    return *this;
}


template<>
WordValue<WordArg::REG_DE>::operator Word() const {
    return emulator.cpu.registers.de;
}

template<>
WordValue<WordArg::REG_DE> &WordValue<WordArg::REG_DE>::operator=(Word value) {
    emulator.cpu.registers.de = value;
    return *this;
}


template<>
WordValue<WordArg::REG_HL>::operator Word() const {
    return emulator.cpu.registers.hl;
}

template<>
WordValue<WordArg::REG_HL> &WordValue<WordArg::REG_HL>::operator=(Word value) {
    emulator.cpu.registers.hl = value;
    return *this;
}


template<>
WordValue<WordArg::REG_SP>::operator Word() const {
    return emulator.cpu.registers.sp;
}

template<>
WordValue<WordArg::REG_SP> &WordValue<WordArg::REG_SP>::operator=(Word value) {
    emulator.cpu.registers.sp = value;
    return *this;
}

}
