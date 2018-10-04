#ifndef GAMEBOY_EMULATOR_MBC1_H
#define GAMEBOY_EMULATOR_MBC1_H


#include "MemoryBankController.hpp"

namespace nsfgbe {

class MBC1 : public MemoryBankController {
private:
    enum class Mode : Byte {
        LARGE_ROM,
        SMALL_ROM,
    };

    Mode mode = Mode::LARGE_ROM;
    bool ramEnabled = false;
    Byte romBank = 1;

public:
    void setByte(Address address, Byte value) override;

    explicit MBC1(MMU &mmu);
};

}


#endif //GAMEBOY_EMULATOR_MBC1_H
