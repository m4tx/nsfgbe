#include "CPU.hpp"

namespace nsfgbe {

bool CPU::getFlag(Byte flag) const {
    return registers.f & flag;
}

void CPU::setFlag(Byte flag) {
    registers.f |= flag;
}

void CPU::setFlag(Byte flag, bool set) {
    if (set) {
        setFlag(flag);
    } else {
        resetFlag(flag);
    }
}

void CPU::resetFlag(Byte flag) {
    registers.f &= ~flag;
}

}
