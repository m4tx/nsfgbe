#include "GPURegisters.hpp"
#include "emulator/gpu/GPU.hpp"

namespace nsfgbe {

GPURegisters::GPURegisters(GPU &gpu) :
        scy(0x00),
        scx(0x00),
        ly(0x00),
        lyc(0x00),
        dma(gpu.dma),
        bgp(0xFC),
        obp0(0xFF),
        obp1(0xFF),
        wy(0x00),
        wx(0x00),
        MMIORegisterStore(std::array<BaseMMIORegister *, 12>{
                &lcdc,
                &stat,
                &scy,
                &scx,
                &ly,
                &lyc,
                &dma,
                &bgp,
                &obp0,
                &obp1,
                &wy,
                &wx,
        }, 0xFF40) {}

}
