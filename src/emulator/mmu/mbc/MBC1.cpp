#include <iostream>

#include "MBC1.hpp"

#include <emulator/mmu/MMU.hpp>

namespace gb {

MBC1::MBC1(MMU &mmu) : MemoryBankController(mmu) {}

void MBC1::setByte(Address address, Byte value) {
    if (address >= 0x0000 && address < 0x2000) {
        ramEnabled = value == 0x0A;
    } else if (address >= 0x2000 && address < 0x4000) {
        if (value == 0) {
            value = 1;
        }

        value &= 0x1F;
        romBank = (romBank & 0x60_b) + value;

        mmu.romBankOffset = 0x4000_adr * romBank;
    } else if (address >= 0x4000 && address < 0x6000) {
        if (mode == Mode::LARGE_ROM) {
            romBank = (romBank & 0x1F_b) | ((value & 3_b) << 5);
            mmu.romBankOffset = 0x4000_adr * romBank;
        } else {
            mmu.externalRamOffset = 0x2000_adr * (value & 3_b);
        }
    } else if (address >= 0x6000 && address < 0x8000) {
        mode = static_cast<Mode>(value & 1);
    }
}

}
