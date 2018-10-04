#ifndef GAMEBOY_EMULATOR_SERIALLINKMANAGER_H
#define GAMEBOY_EMULATOR_SERIALLINKMANAGER_H


#include <vector>
#include <emulator/mmu/MMIORegisterStore.hpp>

#include "SIODataRegister.hpp"
#include "SIOControlRegister.hpp"

namespace nsfgbe {

class SerialLinkManager : public MMIORegisterStore<2> {
private:
    SIODataRegister sioDataRegister;
    SIOControlRegister sioControlRegister;

    friend class SIODataRegister;

    std::vector<Byte> dataSent;

    void sendByte(Byte value);

public:
    SerialLinkManager();

    const std::vector<Byte> &getDataSent() const;
};

}


#endif //GAMEBOY_EMULATOR_SERIALLINKMANAGER_H
