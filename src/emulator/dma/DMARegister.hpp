#ifndef GAMEBOY_EMULATOR_DMAREGISTER_H
#define GAMEBOY_EMULATOR_DMAREGISTER_H


#include <emulator/mmu/MMIORegister.hpp>
#include "DMA.hpp"

namespace gb {

class DMARegister : public BaseMMIORegister {
private:
    DMA &dma;

protected:
    Byte getValue() const override;

    void setValue(Byte value) override;

public:
    explicit DMARegister(DMA &dma);
};

}


#endif //GAMEBOY_EMULATOR_DMAREGISTER_H
