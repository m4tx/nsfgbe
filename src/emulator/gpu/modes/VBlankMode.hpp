#ifndef GAMEBOY_EMULATOR_VBLANKMODE_H
#define GAMEBOY_EMULATOR_VBLANKMODE_H


#include "GPUMode.hpp"

namespace nsfgbe {

class VBlankMode : public GPUMode {
protected:
    void doStart() override;

    bool doTick() override;

public:
    VBlankMode(GPU &gpu);
};

}


#endif //GAMEBOY_EMULATOR_VBLANKMODE_H
