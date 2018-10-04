#include <iostream>

#include "MemoryBankController.hpp"
#include "DummyMBC.hpp"
#include "MBC1.hpp"

namespace gb {

MemoryBankController::MemoryBankController(MMU &mmu) : mmu(mmu) {}

std::unique_ptr<MemoryBankController>
MemoryBankController::getMBC(ROM::ROMType romType, MMU &mmu) {
    switch (romType) {
        case ROM::ROMType::ROM_ONLY:
            return std::unique_ptr<MemoryBankController>(new DummyMBC(mmu));
        case ROM::ROMType::ROM_MBC1:
        case ROM::ROMType::ROM_MBC1_RAM:
        case ROM::ROMType::ROM_MBC1_RAM_BATT:
            return std::unique_ptr<MemoryBankController>(new MBC1(mmu));
        case ROM::ROMType::ROM_MBC2:
        case ROM::ROMType::ROM_MBC2_BATT:
        case ROM::ROMType::ROM_RAM:
        case ROM::ROMType::ROM_RAM_BATT:
        default:
            throw std::logic_error("Unsupported ROM type!");
    }
}

}
