#ifndef GAMEBOY_EMULATOR_TIMERCONTROLREGISTER_H
#define GAMEBOY_EMULATOR_TIMERCONTROLREGISTER_H


#include <emulator/mmu/MMIORegister.hpp>

namespace gb {

class Timer;

/**
 * Timer Control Register (TAC / 0xFF07) implementation.
 */
class TimerControlRegister : public MMIORegister<MMIOPermissions::READ_WRITE> {
private:
    Timer &timer;

protected:
    void setValue(Byte value) override;

public:
    explicit TimerControlRegister(Timer &timer);

    TimerControlRegister &operator=(Byte value) override;
};

}


#endif //GAMEBOY_EMULATOR_TIMERCONTROLREGISTER_H
