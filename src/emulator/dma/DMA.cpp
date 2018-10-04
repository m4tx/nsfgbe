#include "DMA.hpp"

#include <emulator/Constants.hpp>
#include <emulator/mmu/MMU.hpp>

namespace gb {

DMA::DMA(MMU &mmu) : mmu(mmu) {}

void DMA::startTransfer(Byte page) {
    totalTicks = 0;
    startAddress = static_cast<Address>(page * 0x100);
    running = true;

    // todo don't allow access to anything except HRAM during the DMA transfer
}

void DMA::tick(size_t ticks) {
    if (!running) {
        return;
    }

    totalTicks += ticks;

    if (totalTicks >= DMA_TICKS) {
        for (size_t i = 0; i < OAM_RAM_SIZE; ++i) {
            mmu[0xFE00 + i] = mmu[startAddress + i];
        }

        running = false;
    }
}

}
