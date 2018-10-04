#include "PixelTransferMode.hpp"

#include <iostream>

#include <emulator/gpu/GPU.hpp>
#include <emulator/Constants.hpp>

namespace nsfgbe {

PixelTransferMode::PixelTransferMode(GPU &gpu) :
        GPUMode(gpu),
        fetcher(gpu, pixelFifo) {}

void PixelTransferMode::doStart() {
    currentX = 0;
    Byte scanline = gpu.registers.ly + gpu.registers.scy;
    Byte backgroundX = gpu.registers.scx;
    pixelsToDrop = backgroundX % 8_b;

    fetcher.fetch(static_cast<Word>(scanline / 8 * 32 + backgroundX / 8),
                  static_cast<Byte>(scanline % 8));
    pixelFifo.clear();
}

bool PixelTransferMode::doTick() {
    if (totalTicks != 0 && totalTicks % 2 == 0) {
        // Make fetcher ticks every second tick of the GPU clock
        fetcher.tick();
    }

    if (canRetrievePixel() && pixelsToDrop != 0) {
        pixelFifo.dropPixels(pixelsToDrop);
        pixelsToDrop = 0;
    }

    if (!fetcher.isFetchingSprite() && pixelFifo.canRetrievePixel()) {
        for (Byte spriteId : gpu.visibleSprites) {
            if (spriteId < lastSprite) {
                continue;
            }

            Byte scanline = gpu.registers.ly;
            OAMEntry &entry = gpu.oamRam[spriteId];
            if (entry.x == currentX + 8 || (currentX == 0 && entry.x < 8)) {
                fetcher.fetchSprite(
                        spriteId,
                        scanline - (entry.y - 16_b),
                        currentX + 8_b - entry.x);
                lastSprite = spriteId + 1;

                break;
            }
        }
    }

    if (canRetrievePixel()) {
        Pixel pixel = pixelFifo.retrievePixel();

        const Palette &palette = getPaletteForSource(pixel.source);
        gpu.pixelBuffer[gpu.currentPixel++] = palette[pixel.value].toRGB();

        ++currentX;
        lastSprite = 0;
    }

    if (currentX >= 160) {
        return true;
    }

    return false;
}

bool PixelTransferMode::canRetrievePixel() const {
    return pixelFifo.canRetrievePixel() &&
           !fetcher.isFetchingSprite() &&
           gpu.currentPixel < SCREEN_WIDTH * SCREEN_HEIGHT;
}

const Palette &PixelTransferMode::getPaletteForSource(PixelSource source) {
    switch (source) {
        case PIXEL_SOURCE_BG:
            return gpu.registers.bgp.getPalette();
        case PIXEL_SOURCE_OB0:
            return gpu.registers.obp0.getPalette();
        case PIXEL_SOURCE_OB1:
            return gpu.registers.obp1.getPalette();
        default:
            throw std::logic_error("Invalid PixelSource");
    }
}

}
