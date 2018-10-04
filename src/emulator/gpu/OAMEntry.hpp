#ifndef GAMEBOY_EMULATOR_OAMENTRY_H
#define GAMEBOY_EMULATOR_OAMENTRY_H


#include <Types.hpp>

namespace gb {

struct OAMEntry {
    enum class Flags : Byte {
        PRIORITY = 1 << 7,
        Y_FLIP = 1 << 6,
        X_FLIP = 1 << 5,
        PALETTE = 1 << 4,
    };

    Byte y;
    Byte x;
    Byte pattern;
    Byte flags;

    bool getFlag(Flags flag) const;
};

}


#endif //GAMEBOY_EMULATOR_OAMENTRY_H
