#ifndef GAMEBOY_EMULATOR_TIMER_H
#define GAMEBOY_EMULATOR_TIMER_H


#include <cstddef>
#include <array>

#include <Types.hpp>
#include <emulator/mmu/BaseMMIORegister.hpp>
#include <emulator/mmu/MMIORegister.hpp>
#include <emulator/interrupt/InterruptManager.hpp>

#include "DividerRegister.hpp"
#include "TimerControlRegister.hpp"

namespace nsfgbe {

class Timer {
public:
    enum class Frequency {
        FREQ_4K,
        FREQ_262K,
        FREQ_65K,
        FREQ_16K,
    };

private:
    const size_t DIVIDER_STEP = 1 << 8;

    const std::array<size_t, 4> FREQUENCY_MAP{
            0x400,
            0x10,
            0x40,
            0x100,
    };

    InterruptManager &interruptManager;

    /** DIV Register (0xFF04) */
    DividerRegister dividerRegister;
    /** TIMA Register (0xFF05) */
    MMIORegister<MMIOPermissions::READ_WRITE> timerCounterRegister;
    /** TMA Register (0xFF06) */
    MMIORegister<MMIOPermissions::READ_WRITE> timerModuloRegister;
    /** TAC Register (0xFF07) */
    TimerControlRegister timerControlRegister;

    size_t totalTicks;

    Byte divider = 0;

    size_t counterStep = FREQUENCY_MAP[static_cast<size_t>(Frequency::FREQ_4K)];
    bool counterEnabled = false;

    friend class MMU;

    friend class DividerRegister;

    friend class TimerControlRegister;

    void setCounterFrequency(Frequency frequency);

public:
    explicit Timer(InterruptManager &interruptManager);

    void tick(size_t ticks);
};

}


#endif //GAMEBOY_EMULATOR_TIMER_H
