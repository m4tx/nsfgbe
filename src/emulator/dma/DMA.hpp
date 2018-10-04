#ifndef GAMEBOY_EMULATOR_DMA_H
#define GAMEBOY_EMULATOR_DMA_H


#include <cstddef>

#include <Types.hpp>

namespace nsfgbe {

class MMU;

class DMA {
private:
    MMU &mmu;

    bool running = false;
    size_t totalTicks = 0;
    Address startAddress;

public:
    explicit DMA(MMU &mmu);

    void startTransfer(Byte page);

    void tick(size_t ticks);
};

}


#endif //GAMEBOY_EMULATOR_DMA_H
