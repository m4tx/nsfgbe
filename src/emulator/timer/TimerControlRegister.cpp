#include "TimerControlRegister.hpp"
#include "Timer.hpp"

namespace gb {

TimerControlRegister::TimerControlRegister(Timer &timer) :
        MMIORegister(0x00),
        timer(timer) {}


void TimerControlRegister::setValue(Byte value) {
    MMIORegister::setValue(value);

    timer.counterEnabled = ((value >> 2) & 1) != 0;
    timer.setCounterFrequency(static_cast<Timer::Frequency>(value & 3));
}

TimerControlRegister &TimerControlRegister::operator=(Byte value) {
    setValue(value);
    return *this;
}

}
