#include "JoypadRegister.hpp"

namespace gb {

JoypadRegister::JoypadRegister(const InputHandler &inputHandler) :
        inputHandler(inputHandler) {}

Byte JoypadRegister::getValue() const {
    Byte value = 0;

    if (dpadEnabled) {
        value |= DPAD_ENABLED_MASK;
        value |= getPressedKeyMask(0);
    }
    if (buttonsEnabled) {
        value |= BUTTONS_ENABLED_MASK;
        value |= getPressedKeyMask(4);
    }

    return value;
}

Byte JoypadRegister::getPressedKeyMask(Byte offset) const {
    Byte value = 0;

    for (Byte i = 0; i < 4; ++i) {
        bool pressed = inputHandler.isPressed(
                static_cast<InputHandler::Key>(i + offset));
        value |= !pressed << i;
    }

    return value;
}

void JoypadRegister::setValue(Byte value) {
    dpadEnabled = (value & DPAD_ENABLED_MASK) != 0;
    buttonsEnabled = (value & BUTTONS_ENABLED_MASK) != 0;
}

JoypadRegister &JoypadRegister::operator=(Byte value) {
    setValue(value);
    return *this;
}

}
