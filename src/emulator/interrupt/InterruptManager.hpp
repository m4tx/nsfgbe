#ifndef GAMEBOY_EMULATOR_INTERRUPTMANAGER_H
#define GAMEBOY_EMULATOR_INTERRUPTMANAGER_H


#include <bitset>
#include <emulator/mmu/MMIORegister.hpp>

namespace gb {

class InterruptManager {
private:
    int enableTicks = 0;
    int disableTicks = 0;

    bool enabled = false;
    bool interruptFired = false;

    MMIORegister<MMIOPermissions::READ_WRITE> ifReg;
    MMIORegister<MMIOPermissions::READ_WRITE> ieReg;

    friend class MMU;

    void fireInterrupt();

public:
    static const Address NO_INTERRUPT = 0;

    InterruptManager();

    Address tick();

    bool isEnabled() const;

    void scheduleInterruptEnable();

    void scheduleInterruptDisable();

    void disableInterrupts();

    void fireVBlankInterrupt();

    void fireLcdcInterrupt();

    void fireTimerInterrupt();

    void fireSerialTransferInterrupt();

    void fireKeypadInterrupt();

    bool checkInterruptFired();
};

}


#endif //GAMEBOY_EMULATOR_INTERRUPTMANAGER_H
