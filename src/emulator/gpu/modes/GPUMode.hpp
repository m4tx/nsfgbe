#ifndef GAMEBOY_EMULATOR_GPUMODE_H
#define GAMEBOY_EMULATOR_GPUMODE_H


#include <cstddef>

namespace nsfgbe {

class GPU;

class GPUMode {
protected:
    GPU &gpu;
    size_t totalTicks = 0;

    virtual void doStart() = 0;

    virtual bool doTick() = 0;

public:
    explicit GPUMode(GPU &gpu);

    void start();

    bool tick();
};

}


#endif //GAMEBOY_EMULATOR_GPUMODE_H
