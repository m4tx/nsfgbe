#include "VBlankMode.hpp"

#include <emulator/gpu/GPU.hpp>

namespace nsfgbe {

VBlankMode::VBlankMode(GPU &gpu) : GPUMode(gpu) {}

void VBlankMode::doStart() {
    gpu.currentPixel = 0;

}

bool VBlankMode::doTick() {
    if (totalTicks % 456 == 0) {
        ++gpu.registers.ly;
    }

    if (totalTicks >= 4560) {
        return true;
    }

    return false;
}

}
