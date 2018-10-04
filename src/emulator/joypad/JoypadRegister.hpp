#ifndef GAMEBOY_EMULATOR_JOYPADREGISTER_H
#define GAMEBOY_EMULATOR_JOYPADREGISTER_H


#include <emulator/mmu/BaseMMIORegister.hpp>
#include <frontends/InputHandler.hpp>

namespace gb {

class JoypadRegister : public BaseMMIORegister {
private:
    const InputHandler &inputHandler;
    bool dpadEnabled;
    bool buttonsEnabled;

    const Byte DPAD_ENABLED_MASK = 1 << 5;
    const Byte BUTTONS_ENABLED_MASK = 1 << 4;

    Byte getPressedKeyMask(Byte offset) const;

protected:
    Byte getValue() const override;

    void setValue(Byte value) override;

public:
    explicit JoypadRegister(const InputHandler &inputHandler);

    JoypadRegister &operator=(Byte value) override;
};

}


#endif //GAMEBOY_EMULATOR_JOYPADREGISTER_H
