#ifndef GAMEBOY_EMULATOR_PIXELTRANSFERMODE_H
#define GAMEBOY_EMULATOR_PIXELTRANSFERMODE_H


#include "GPUMode.hpp"

#include <emulator/gpu/Fetcher.hpp>
#include <emulator/gpu/registers/PaletteRegister.hpp>

namespace gb {

class PixelTransferMode : public GPUMode {
protected:
    void doStart() override;

    bool doTick() override;

    PixelFIFO pixelFifo;
    Fetcher fetcher;

    Byte currentX;
    size_t lastSprite = 0;

    /**
     * When scx is not a multiplication of 8, we need to drop this many pixels
     * before putting them to the screen.
     */
    Byte pixelsToDrop = 0;

    const Palette &getPaletteForSource(PixelSource source);

    bool canRetrievePixel() const;

public:
    PixelTransferMode(GPU &gpu);
};

}


#endif //GAMEBOY_EMULATOR_PIXELTRANSFERMODE_H
