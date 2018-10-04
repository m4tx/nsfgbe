#ifndef GAMEBOY_EMULATOR_DIVIDERREGISTER_H
#define GAMEBOY_EMULATOR_DIVIDERREGISTER_H


#include <emulator/mmu/BaseMMIORegister.hpp>

namespace nsfgbe {

class Timer;

/**
 * Timer Divider Register (DIV / 0xFF04) implementation.
 */
class DividerRegister : public BaseMMIORegister {
private:
    Timer &timer;

protected:
    Byte getValue() const override;

    void setValue(Byte value) override;

public:
    explicit DividerRegister(Timer &timer);

    DividerRegister &operator=(Byte value) override;
};

}


#endif //GAMEBOY_EMULATOR_DIVIDERREGISTER_H
