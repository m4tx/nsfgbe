#ifndef GAMEBOY_EMULATOR_MEMORYBANKCONTROLLER_H
#define GAMEBOY_EMULATOR_MEMORYBANKCONTROLLER_H


#include <memory>

#include <Types.hpp>
#include <rom/ROM.hpp>

namespace gb {

class MMU;

class MemoryBankController {
protected:
    MMU &mmu;

public:
    explicit MemoryBankController(MMU &mmu);

    virtual void setByte(Address address, Byte value) = 0;

    static std::unique_ptr<MemoryBankController>
    getMBC(ROM::ROMType romType, MMU &mmu);
};

}


#endif //GAMEBOY_EMULATOR_MEMORYBANKCONTROLLER_H
