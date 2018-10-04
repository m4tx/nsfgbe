#include "SIODataRegister.hpp"
#include "SerialLinkManager.hpp"

namespace nsfgbe {

SIODataRegister::SIODataRegister(SerialLinkManager &serialLinkManager)
        : MMIORegister(0x00), serialLinkManager(serialLinkManager) {}

SIODataRegister &SIODataRegister::operator=(Byte value) {
    setValue(value);
    return *this;
}

Byte SIODataRegister::getValue() const {
    return MMIORegister::getValue();
}

void SIODataRegister::setValue(Byte value) {
    MMIORegister::setValue(value);
    serialLinkManager.sendByte(value);
}

}
