#include "LCDCRegister.hpp"

namespace gb {

LCDCRegister::LCDCRegister() : MMIORegister(0x91) {}

LCDCRegister &LCDCRegister::operator=(Byte value) {
    setValue(value);
    return *this;
}

bool LCDCRegister::isBgAndWindowDisplayed() const {
    return ((value >> 0) & 1) != 0;
}

bool LCDCRegister::isSpriteDisplayed() const {
    return ((value >> 1) & 1) != 0;
}

Byte LCDCRegister::getSpriteHeight() const {
    return ((value >> 2) & 1) == 0 ? 8_b : 16_b;
}

Address LCDCRegister::getBgTileMapAddress() const {
    return ((value >> 3) & 1) == 0 ? 0x1800_adr : 0x1C00_adr;
}

Address LCDCRegister::getBgTileAddress(Byte tile) const {
    if (((value >> 4) & 1) == 0) {
        return static_cast<Address>(0x1000 + 16 * static_cast<int8_t>(tile));
    } else {
        return static_cast<Address>(0x0000 + 16 * tile);
    }
}

bool LCDCRegister::isWindowDisplayed() const {
    return ((value >> 5) & 1) != 0;
}

Address LCDCRegister::getWindowTileMapAddress() const {
    return ((value >> 6) & 1) == 0 ? 0x1800_adr : 0x1C00_adr;
}

bool LCDCRegister::isLCDEnabled() const {
    return ((value >> 7) & 1) != 0;
}

}
