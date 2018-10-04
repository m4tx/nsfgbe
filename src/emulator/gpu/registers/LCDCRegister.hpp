#ifndef GAMEBOY_EMULATOR_LCDCREGISTER_H
#define GAMEBOY_EMULATOR_LCDCREGISTER_H


#include <emulator/mmu/MMIORegister.hpp>

namespace gb {

class LCDCRegister : public MMIORegister<MMIOPermissions::READ_WRITE> {
public:
    LCDCRegister();

    LCDCRegister &operator=(Byte value) override;

    /** Controlled by bit 0. */
    bool isBgAndWindowDisplayed() const;

    /** Controlled by bit 1. */
    bool isSpriteDisplayed() const;

    /** Controlled by bit 2. */
    Byte getSpriteHeight() const;

    /** Controlled by bit 3. */
    Address getBgTileMapAddress() const;

    /** Controlled by bit 4. */
    Address getBgTileAddress(Byte tile) const;

    /** Controlled by bit 5. */
    bool isWindowDisplayed() const;

    /** Controlled by bit 6. */
    Address getWindowTileMapAddress() const;

    /** Controlled by bit 7. */
    bool isLCDEnabled() const;
};

}


#endif //GAMEBOY_EMULATOR_LCDCREGISTER_H
