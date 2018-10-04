#ifndef GAMEBOY_EMULATOR_PALETTEREGISTER_H
#define GAMEBOY_EMULATOR_PALETTEREGISTER_H


#include <array>

#include <emulator/mmu/MMIORegister.hpp>

#include "emulator/gpu/GPUTypes.hpp"
#include "emulator/gpu/RGBPixel.hpp"

namespace nsfgbe {

typedef std::array<RGBPixel, 4> Palette;

class PaletteRegister : public MMIORegister<MMIOPermissions::READ_WRITE> {
private:
    Palette palette;

    static constexpr Palette PALETTE_MAP{
            RGBPixel{0xF7, 0xE7, 0xC6},
            RGBPixel{0xD6, 0x8E, 0x49},
            RGBPixel{0xA6, 0x37, 0x25},
            RGBPixel{0x33, 0x1E, 0x50},
    };

    void recreatePalette();

protected:
    void setValue(Byte value) override;

public:
    explicit PaletteRegister(Byte value);

    PaletteRegister &operator=(Byte value) override;

    const Palette &getPalette() const;
};

}


#endif //GAMEBOY_EMULATOR_PALETTEREGISTER_H
