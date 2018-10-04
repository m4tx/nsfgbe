#ifndef GAMEBOY_EMULATOR_GPUREGISTERS_H
#define GAMEBOY_EMULATOR_GPUREGISTERS_H


#include <emulator/mmu/MMIORegisterStore.hpp>
#include <emulator/mmu/MMIORegister.hpp>
#include <emulator/dma/DMARegister.hpp>
#include "PaletteRegister.hpp"
#include "LCDCRegister.hpp"
#include "STATRegister.hpp"

namespace nsfgbe {

class GPU;

class GPURegisters : public MMIORegisterStore<12> {
public:
    /** LCD Control */
    LCDCRegister lcdc;

    /** LCD Status */
    STATRegister stat;

    /** Scroll Y */
    MMIORegister<MMIOPermissions::READ_WRITE> scy;

    /** Scroll X */
    MMIORegister<MMIOPermissions::READ_WRITE> scx;

    /** LCDC Y-Coordinate */
    MMIORegister<MMIOPermissions::READ> ly;

    /** LY Compare */
    MMIORegister<MMIOPermissions::READ_WRITE> lyc;

    /** DMA Transfer and Start Address */
    DMARegister dma;

    /** BG & Window Palette Data */
    PaletteRegister bgp;

    /** Object Palette 0 Data */
    PaletteRegister obp0;

    /** Object Palette 1 Data */
    PaletteRegister obp1;

    /** Window Y Position */
    MMIORegister<MMIOPermissions::READ_WRITE> wy;

    /** Window X Position */
    MMIORegister<MMIOPermissions::READ_WRITE> wx;

public:
    explicit GPURegisters(GPU &gpu);
};

}


#endif //GAMEBOY_EMULATOR_GPUREGISTERS_H
