#include "GPUMode.hpp"

namespace nsfgbe {

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
