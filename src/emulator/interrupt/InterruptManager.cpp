#include "InterruptManager.hpp"

#include <emulator/cpu/instructions/impl/Calls.hpp>

namespace nsfgbe {

InterruptManager::InterruptManager() :
        ifReg(0x0),
        ieReg(0x0) {}

Address InterruptManager::tick() {
    if (enableTicks > 0) {
        --enableTicks;
        if (enableTicks == 0) {
            enabled = true;
        }
    }

    if (disableTicks > 0) {
        --disableTicks;
        if (disableTicks == 0) {
            enabled = false;
        }
    }

    if (!enabled) {
        return NO_INTERRUPT;
    }

    for (Byte i = 0; i < 5; ++i) {
        int mask = 1 << i;
        if ((ieReg & ifReg & mask) != 0) {
            ifReg = 0;
            return 0x40_adr + i * 8_adr;
        }
    }

    return NO_INTERRUPT;
}

bool InterruptManager::isEnabled() const {
    return enabled;
}

void InterruptManager::scheduleInterruptEnable() {
    enableTicks = 2;
}

void InterruptManager::scheduleInterruptDisable() {
    disableTicks = 2;
}

void InterruptManager::disableInterrupts() {
    enabled = false;
}

void InterruptManager::fireVBlankInterrupt() {
    ifReg |= 1 << 0;
    fireInterrupt();
}

void InterruptManager::fireLcdcInterrupt() {
    ifReg |= 1 << 1;
    fireInterrupt();
}

void InterruptManager::fireTimerInterrupt() {
    ifReg |= 1 << 2;
    fireInterrupt();
}

void InterruptManager::fireSerialTransferInterrupt() {
    ifReg |= 1 << 3;
    fireInterrupt();
}

void InterruptManager::fireKeypadInterrupt() {
    ifReg |= 1 << 4;
    fireInterrupt();
}

void InterruptManager::fireInterrupt() {
    interruptFired = true;
}

bool InterruptManager::checkInterruptFired() {
    if (interruptFired) {
        interruptFired = false;
        return true;
    }

    return false;
}

}
