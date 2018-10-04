#ifndef GAMEBOY_EMULATOR_HBLANKMODE_H
#define GAMEBOY_EMULATOR_HBLANKMODE_H


#include "GPUMode.hpp"

namespace gb {

class HBlankMode : public GPUMode {
protected:
    void doStart() override;

    bool doTick() override;

public:
    HBlankMode(GPU &gpu);
};

}


#endif //GAMEBOY_EMULATOR_HBLANKMODE_H
