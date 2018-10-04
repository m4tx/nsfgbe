#include "SIOControlRegister.hpp"

namespace nsfgbe {

SIOControlRegister::SIOControlRegister(SerialLinkManager &serialLinkManager)
        : MMIORegister(0x00), serialLinkManager(serialLinkManager) {}

SIOControlRegister &SIOControlRegister::operator=(Byte value) {
    setValue(value);
    return *this;
}

Byte SIOControlRegister::getValue() const {
    return MMIORegister::getValue();
}

void SIOControlRegister::setValue(Byte value) {
    MMIORegister::setValue(value);
}

}
