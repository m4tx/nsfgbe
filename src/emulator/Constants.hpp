#ifndef GAMEBOY_EMULATOR_CONSTANTS_H
#define GAMEBOY_EMULATOR_CONSTANTS_H


#include <cstddef>

#include <Types.hpp>

namespace nsfgbe {

const size_t SCREEN_WIDTH = 160;
const size_t SCREEN_HEIGHT = 144;

const size_t ROM_SIZE = 0x4000;
const size_t RAM_SIZE = 0x2000;
const size_t HIGH_RAM_SIZE = 127;

const size_t VRAM_SIZE = 0x2000;
const size_t OAM_ENTRY_NUMBER = 40;
const size_t OAM_ENTRY_SIZE = 4;
const size_t OAM_RAM_SIZE = OAM_ENTRY_NUMBER * OAM_ENTRY_SIZE;
const size_t VISIBLE_SPRITE_NUMBER = 10;

const Address VRAM_ADDRESS = 0x8000;

const size_t DMA_TICKS = 671;

}


#endif //GAMEBOY_EMULATOR_CONSTANTS_H
