#include "Timer.hpp"

namespace gb {

Timer::Timer(InterruptManager &interruptManager) :
        interruptManager(interruptManager),
        dividerRegister(*this),
        timerCounterRegister(0),
        timerModuloRegister(0),
        timerControlRegister(*this) {}

void Timer::tick(size_t ticks) {
    size_t newTotalTicks = totalTicks + ticks;
    size_t tickXor = totalTicks ^newTotalTicks;

    if (tickXor & DIVIDER_STEP) {
        ++divider;
    }

    if (counterEnabled && (tickXor & counterStep)) {
        ++timerCounterRegister;
        if (timerCounterRegister == 0) {
            timerCounterRegister = timerModuloRegister;
            interruptManager.fireTimerInterrupt();
        }
    }

    totalTicks = newTotalTicks;
}

void Timer::setCounterFrequency(Timer::Frequency frequency) {
    counterStep = FREQUENCY_MAP[frequency];
}

}
