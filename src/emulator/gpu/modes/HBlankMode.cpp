#include "HBlankMode.hpp"

namespace nsfgbe {

HBlankMode::HBlankMode(GPU &gpu) : GPUMode(gpu) {}

void HBlankMode::doStart() {

}

bool HBlankMode::doTick() {
    if (totalTicks >= 204) {
        return true;
    }

    return false;
}

}
