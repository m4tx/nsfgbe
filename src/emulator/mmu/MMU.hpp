#ifndef GAMEBOY_EMULATOR_MMU_H
#define GAMEBOY_EMULATOR_MMU_H


#include <cstdint>
#include <vector>
#include <memory>

#include <Types.hpp>
#include <emulator/gpu/GPU.hpp>
#include <emulator/joypad/JoypadRegister.hpp>
#include <emulator/timer/Timer.hpp>
#include <emulator/mmu/mbc/MemoryBankController.hpp>
#include <emulator/serial/SerialLinkManager.hpp>

namespace gb {

class MMU {
private:
    InterruptManager &interruptManager;
    SerialLinkManager &serialLinkManager;
    GPU &gpu;
    JoypadRegister &joypadRegister;
    Timer &timer;

    std::vector<Byte> ram;
    std::vector<Byte> highRam;

    Address externalRamOffset = 0x0000;
    std::vector<Byte> externalRam;

    Address romBankOffset = 0x4000;
    std::vector<Byte> rom;

    friend class MBC1;

    std::unique_ptr<MemoryBankController> mbc;

    class Reference {
    private:
        MMU &mmu;
        Address address;

        friend MMU;

        Reference(MMU &mmu, Address address);

    public:
        operator Byte() const;

        Reference &operator=(Byte value);

        Reference &operator=(const Reference &value);
    };

public:
    MMU(const ROM &rom, InterruptManager &interruptManager,
        SerialLinkManager &serialLinkManager,
        GPU &gpu, JoypadRegister &joypadRegister, Timer &timer);

    Byte getByte(Address address) const;

    Word getWord(Address address) const;

    void setByte(Address address, Byte value);

    void setWord(Address address, Word value);

    const Byte operator[](Address address) const;

    Reference operator[](Address address);
};

}


#endif //GAMEBOY_EMULATOR_MMU_H
