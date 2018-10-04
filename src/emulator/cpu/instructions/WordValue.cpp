#include "WordValue.hpp"

namespace nsfgbe {

template<>
WordValue<ARG_REG_AF>::operator Word() const {
    return emulator.cpu.registers.af & 0xFFF0_w;
}

template<>
WordValue<ARG_REG_AF> &WordValue<ARG_REG_AF>::operator=(Word value) {
    emulator.cpu.registers.af = value & 0xFFF0_w;
    return *this;
}


template<>
WordValue<ARG_REG_BC>::operator Word() const {
    return emulator.cpu.registers.bc;
}

template<>
WordValue<ARG_REG_BC> &WordValue<ARG_REG_BC>::operator=(Word value) {
    emulator.cpu.registers.bc = value;
    return *this;
}


template<>
WordValue<ARG_REG_DE>::operator Word() const {
    return emulator.cpu.registers.de;
}

template<>
WordValue<ARG_REG_DE> &WordValue<ARG_REG_DE>::operator=(Word value) {
    emulator.cpu.registers.de = value;
    return *this;
}


template<>
WordValue<ARG_REG_HL>::operator Word() const {
    return emulator.cpu.registers.hl;
}

template<>
WordValue<ARG_REG_HL> &WordValue<ARG_REG_HL>::operator=(Word value) {
    emulator.cpu.registers.hl = value;
    return *this;
}


template<>
WordValue<ARG_REG_SP>::operator Word() const {
    return emulator.cpu.registers.sp;
}

template<>
WordValue<ARG_REG_SP> &WordValue<ARG_REG_SP>::operator=(Word value) {
    emulator.cpu.registers.sp = value;
    return *this;
}

}
