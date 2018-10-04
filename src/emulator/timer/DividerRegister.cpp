#include <iostream>
#include "DividerRegister.hpp"
#include "Timer.hpp"

namespace nsfgbe {

DividerRegister::DividerRegister(Timer &timer) : timer(timer) {}

DividerRegister &DividerRegister::operator=(Byte value) {
    setValue(value);
    return *this;
}

Byte DividerRegister::getValue() const {
    return timer.divider;
}

void DividerRegister::setValue(Byte value) {
    // Always set to 0 on write
    timer.divider = 0;
}

}
