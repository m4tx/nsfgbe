#ifndef GAMEBOY_EMULATOR_DUMMYMBC_H
#define GAMEBOY_EMULATOR_DUMMYMBC_H


#include "MemoryBankController.hpp"

namespace nsfgbe {

class DummyMBC : public MemoryBankController {
public:
    explicit DummyMBC(MMU &mmu);

    void setByte(Address address, Byte value) override;
};

}


#endif //GAMEBOY_EMULATOR_DUMMYMBC_H
