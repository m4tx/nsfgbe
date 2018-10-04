#include <emulator/Constants.hpp>
#include <stdexcept>
#include <iostream>
#include "GPU.hpp"

namespace nsfgbe {

GPU::GPU(InterruptManager &interruptManager, DMA &dma, uint32_t *pixelBuffer) :
        interruptManager(interruptManager),
        dma(dma),
        oamSearchMode(*this),
        pixelTransferMode(*this),
        hBlankMode(*this),
        vBlankMode(*this),
        currentMode(&hBlankMode),
        vram(VRAM_SIZE, 0),
        oamRam(OAM_ENTRY_NUMBER, OAMEntry{}),
        pixelBuffer(pixelBuffer),
        registers(*this) {
    visibleSprites.reserve(VISIBLE_SPRITE_NUMBER);
    switchModeTo(gpuMode);
}

void GPU::switchModeTo(GPUModeId mode) {
    gpuMode = mode;
    registers.stat.setMode(mode);

    switch (mode) {
        case GPUModeId::OAM_SEARCH:
            currentMode = &oamSearchMode;
            break;
        case GPUModeId::PIXEL_TRANSFER:
            currentMode = &pixelTransferMode;
            break;
        case GPUModeId::HBLANK:
            currentMode = &hBlankMode;
            break;
        case GPUModeId::VBLANK:
            currentMode = &vBlankMode;
            break;
    }

    if (registers.stat.isInterruptEnabledForMode(mode)) {
        interruptManager.fireLcdcInterrupt();
    }

    currentMode->start();
}

bool GPU::tick(size_t ticks) {
    for (size_t i = 0; i < ticks; ++i) {
        if (currentMode->tick()) {
            switch (gpuMode) {
                case GPUModeId::OAM_SEARCH:
                    switchModeTo(GPUModeId::PIXEL_TRANSFER);
                    break;
                case GPUModeId::PIXEL_TRANSFER:
                    switchModeTo(GPUModeId::HBLANK);
                    break;
                case GPUModeId::HBLANK:
                    if (registers.ly == 143) {
                        switchModeTo(GPUModeId::VBLANK);
                    } else {
                        setCurrentScanline(registers.ly + 1);
                        switchModeTo(GPUModeId::OAM_SEARCH);
                    }
                    break;
                case GPUModeId::VBLANK:
                    interruptManager.fireVBlankInterrupt();
                    setCurrentScanline(0);
                    switchModeTo(GPUModeId::OAM_SEARCH);
                    return true;
            }
        }
    }

    return false;
}

void GPU::setCurrentScanline(Byte value) {
    registers.ly = value;

    bool coincidence = value == registers.lyc;
    registers.stat.setCoincidenceFlag(coincidence);
    if (registers.stat.isCoincidenceInterruptEnabled() && coincidence) {
        interruptManager.fireLcdcInterrupt();
    }
}

}
