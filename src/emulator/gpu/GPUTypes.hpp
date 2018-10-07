#ifndef GAMEBOY_EMULATOR_GPUTYPES_H
#define GAMEBOY_EMULATOR_GPUTYPES_H


#include <Types.hpp>

namespace nsfgbe {

enum class GPUModeId : Byte {
    HBLANK = 0,
    VBLANK = 1,
    OAM_SEARCH = 2,
    PIXEL_TRANSFER = 3,
};

enum class PixelSource : Byte {
    /** Background/window pixel (using background palette) */
    BG,
    /** Object pixel (using sprite palette 0) */
    OB0,
    /** Object pixel (using sprite palette 1) */
    OB1,
};

struct Pixel {
    PixelSource source;
    Byte value;
};

}


#endif //GAMEBOY_EMULATOR_GPUTYPES_H
