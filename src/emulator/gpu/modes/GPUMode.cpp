#include "GPUMode.hpp"

namespace gb {

GPUMode::GPUMode(GPU &gpu) : gpu(gpu) {}

void GPUMode::start() {
    totalTicks = 0;
    doStart();
}

bool GPUMode::tick() {
    bool value = doTick();
    ++totalTicks;
    return value;
}

}
