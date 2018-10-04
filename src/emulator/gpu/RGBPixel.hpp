#ifndef GAMEBOY_EMULATOR_RGBPIXEL_H
#define GAMEBOY_EMULATOR_RGBPIXEL_H


#include <Types.hpp>

namespace gb {

struct RGBPixel {
    Byte r;
    Byte g;
    Byte b;

    uint32_t toRGB() const;
};

}


#endif //GAMEBOY_EMULATOR_RGBPIXEL_H
