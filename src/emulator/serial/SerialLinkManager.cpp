#include "SerialLinkManager.hpp"

namespace nsfgbe {

void SerialLinkManager::sendByte(Byte value) {
    dataSent.push_back(value);
}

SerialLinkManager::SerialLinkManager() :
        sioDataRegister(*this),
        sioControlRegister(*this),

        MMIORegisterStore(std::array<BaseMMIORegister *, 2>{
                &sioDataRegister,
                &sioControlRegister
        }, 0xFF01) {
}

const std::vector<Byte> &SerialLinkManager::getDataSent() const {
    return dataSent;
}

}
