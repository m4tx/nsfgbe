#ifndef GAMEBOY_EMULATOR_GPU_H
#define GAMEBOY_EMULATOR_GPU_H


#include <cstddef>
#include <vector>

#include <Types.hpp>
#include <emulator/gpu/modes/GPUMode.hpp>
#include <emulator/gpu/modes/OAMSearchMode.hpp>
#include <emulator/gpu/modes/PixelTransferMode.hpp>
#include <emulator/gpu/modes/HBlankMode.hpp>
#include <emulator/gpu/modes/VBlankMode.hpp>
#include <emulator/mmu/MMIOHandler.hpp>
#include <emulator/mmu/MMIORegisterStore.hpp>
#include <emulator/interrupt/InterruptManager.hpp>
#include <emulator/dma/DMA.hpp>
#include <emulator/gpu/registers/STATRegister.hpp>

#include "emulator/gpu/registers/GPURegisters.hpp"
#include "OAMEntry.hpp"

namespace nsfgbe {

class GPU {
private:
    InterruptManager &interruptManager;
    DMA &dma;

    GPUModeId gpuMode = GPUModeId::HBLANK;

    OAMSearchMode oamSearchMode;
    PixelTransferMode pixelTransferMode;
    HBlankMode hBlankMode;
    VBlankMode vBlankMode;

    GPUMode *currentMode;

    void switchModeTo(GPUModeId mode);

    std::vector<Byte> vram;
    std::vector<OAMEntry> oamRam;
    std::vector<Byte> visibleSprites;

    GPURegisters registers;

    uint32_t *pixelBuffer;
    unsigned currentPixel = 0;

    void setCurrentScanline(Byte value);

    friend class GPURegisters;

    friend class MMU;

    friend class Fetcher;

    friend class PixelTransferMode;

    friend class OAMSearchMode;

    friend class VBlankMode;

public:
    GPU(InterruptManager &interruptManager, DMA &dma, uint32_t *pixelBuffer);

    bool tick(size_t ticks);
};

}


#endif //GAMEBOY_EMULATOR_GPU_H
