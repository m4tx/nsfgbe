#ifndef GAMEBOY_EMULATOR_OAMSEARCHMODE_H
#define GAMEBOY_EMULATOR_OAMSEARCHMODE_H


#include "GPUMode.hpp"

namespace gb {

class OAMSearchMode : public GPUMode {
protected:
    void doStart() override;

    bool doTick() override;

public:
    explicit OAMSearchMode(GPU &gpu);
};

}


#endif //GAMEBOY_EMULATOR_OAMSEARCHMODE_H
