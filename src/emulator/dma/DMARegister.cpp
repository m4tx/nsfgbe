#include "DMARegister.hpp"

namespace gb {

DMARegister::DMARegister(DMA &dma) : dma(dma) {}

Byte DMARegister::getValue() const {
    return 0xFF;
}

void DMARegister::setValue(Byte value) {
    dma.startTransfer(value);
}

}
