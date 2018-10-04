#ifndef GAMEBOY_EMULATOR_MMIOREGISTERSTORE_H
#define GAMEBOY_EMULATOR_MMIOREGISTERSTORE_H


#include <array>

#include "BaseMMIORegister.hpp"
#include "MMIOHandler.hpp"

namespace nsfgbe {

template<std::size_t N>
class MMIORegisterStore : public MMIOHandler {
protected:
    std::array<BaseMMIORegister *, N> registers;
    Address startAddress;

public:
    MMIORegisterStore(std::array<BaseMMIORegister *, N> &&registers,
                      Address startAddress) :
            registers(registers), startAddress(startAddress) {}

    Byte getMMIOByte(Address address) override {
        return *registers[address - startAddress];
    }

    void setMMIOByte(Address address, Byte value) override {
        *registers[address - startAddress] = value;
    }
};

}


#endif //GAMEBOY_EMULATOR_MMIOREGISTERSTORE_H
