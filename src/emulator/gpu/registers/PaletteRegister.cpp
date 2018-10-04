#include "PaletteRegister.hpp"

namespace nsfgbe {

PaletteRegister::PaletteRegister(Byte value) : MMIORegister(value) {
    recreatePalette();
}

void PaletteRegister::setValue(Byte value) {
    MMIORegister::setValue(value);
    recreatePalette();
}

PaletteRegister &PaletteRegister::operator=(Byte value) {
    setValue(value);
    return *this;
}

void PaletteRegister::recreatePalette() {
    for (int i = 0; i < 4; ++i) {
        Byte index = static_cast<Byte>((value >> (i * 2)) & 0b11);
        palette[i] = PALETTE_MAP[index];
    }
}

const Palette &PaletteRegister::getPalette() const {
    return palette;
}

}
