#include "OAMSearchMode.hpp"
#include <emulator/gpu/GPU.hpp>
#include <emulator/Constants.hpp>

namespace nsfgbe {

OAMSearchMode::OAMSearchMode(GPU &gpu) : GPUMode(gpu) {}

void OAMSearchMode::doStart() {
    gpu.visibleSprites.clear();

    Byte spriteHeight = gpu.registers.lcdc.getSpriteHeight();

    for (Byte i = 0; i < gpu.oamRam.size(); ++i) {
        OAMEntry &entry = gpu.oamRam[i];

        if (entry.x != 0 &&
            gpu.registers.ly + 16 >= entry.y &&
            gpu.registers.ly + 16 < entry.y + spriteHeight) {
            gpu.visibleSprites.push_back(i);

            if (gpu.visibleSprites.size() == VISIBLE_SPRITE_NUMBER) {
                break;
            }
        }
    }
}

bool OAMSearchMode::doTick() {
    if (totalTicks >= 80) {
        return true;
    }

    return false;
}

}
