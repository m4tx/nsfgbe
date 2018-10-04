#ifndef GAMEBOY_EMULATOR_MMIOHANDLER_H
#define GAMEBOY_EMULATOR_MMIOHANDLER_H


#include <Types.hpp>

namespace gb {

class MMIOHandler {
public:
    virtual Byte getMMIOByte(Address address) = 0;

    virtual void setMMIOByte(Address address, Byte value) = 0;
};

}


#endif //GAMEBOY_EMULATOR_MMIOHANDLER_H
