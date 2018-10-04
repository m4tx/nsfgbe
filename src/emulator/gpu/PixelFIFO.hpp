#ifndef GAMEBOY_EMULATOR_PIXELFIFO_H
#define GAMEBOY_EMULATOR_PIXELFIFO_H


#include <queue>
#include <cstdint>
#include <array>

#include <Types.hpp>
#include "GPUTypes.hpp"

namespace gb {

class PixelFIFO {
private:
    std::deque<Pixel> queue;

public:
    PixelFIFO();

    bool canAddEightPixels() const;

    bool canRetrievePixel() const;

    void addEightPixels(const std::array<Pixel, 8> &pixels);

    void addSpritePixels(const std::array<Pixel, 8> &pixels);

    Pixel retrievePixel();

    void dropPixels(Byte amount);

    void clear();
};

}


#endif //GAMEBOY_EMULATOR_PIXELFIFO_H
