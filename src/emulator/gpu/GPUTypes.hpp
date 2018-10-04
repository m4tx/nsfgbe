#ifndef GAMEBOY_EMULATOR_GPUTYPES_H
#define GAMEBOY_EMULATOR_GPUTYPES_H


#include <Types.hpp>

namespace gb {

enum class GPUModeId : Byte {
    HBLANK = 0,
    VBLANK = 1,
    OAM_SEARCH = 2,
    PIXEL_TRANSFER = 3,
};

enum PixelSource {
    /** Background/window pixel (using background palette) */
    PIXEL_SOURCE_BG = 0x0 << 4,
    /** Object pixel (using sprite palette 0) */
    PIXEL_SOURCE_OB0 = 0x1 << 4,
    /** Object pixel (using sprite palette 1) */
    PIXEL_SOURCE_OB1 = 0x2 << 4,
};

struct Pixel {
    PixelSource source;
    Byte value;
};

}


#endif //GAMEBOY_EMULATOR_GPUTYPES_H
