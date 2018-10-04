#include "STATRegister.hpp"

namespace nsfgbe {

STATRegister::STATRegister() : MMIORegister(0) {}

STATRegister &STATRegister::operator=(Byte value) {
    setValue(value);
    return *this;
}

void STATRegister::setValue(Byte value) {
    // Only allow changing the interrupt selection
    MMIORegister::setValue(value & 0b01111000_b);
}

bool STATRegister::isInterruptEnabledForMode(GPUModeId modeId) const {
    if (modeId == GPUModeId::PIXEL_TRANSFER) {
        return false;
    }

    return ((value >> (3 + static_cast<Byte>(modeId))) & 1) != 0;
}

bool STATRegister::isCoincidenceInterruptEnabled() const {
    return ((value >> 6) & 1) != 0;
}

void STATRegister::setCoincidenceFlag(bool flag) {
    value = (value & (~4_b)) | (flag << 2);
}

void STATRegister::setMode(GPUModeId modeId) {
    value = (value & (~3_b)) | static_cast<Byte>(modeId);
}

}
