#include "CPU.hpp"
#include <type_traits>

namespace nsfgbe {

CPUFlags operator|(CPUFlags a, CPUFlags b) {
    return static_cast<CPUFlags> (
            static_cast<std::underlying_type<CPUFlags>::type>(a) |
            static_cast<std::underlying_type<CPUFlags>::type>(b)
    );
}

CPUFlags &operator|=(CPUFlags &a, CPUFlags b) {
    a = static_cast<CPUFlags> (
            static_cast<std::underlying_type<CPUFlags>::type>(a) |
            static_cast<std::underlying_type<CPUFlags>::type>(b)
    );

    return a;
}

Byte &operator|=(Byte &a, CPUFlags b) {
    a |= static_cast<std::underlying_type<CPUFlags>::type>(b);

    return a;
}

CPUFlags operator&(CPUFlags a, CPUFlags b) {
    return static_cast<CPUFlags> (
            static_cast<std::underlying_type<CPUFlags>::type>(a) &
            static_cast<std::underlying_type<CPUFlags>::type>(b)
    );
}

CPUFlags operator&(Byte a, CPUFlags b) {
    return static_cast<CPUFlags> (
            a & static_cast<std::underlying_type<CPUFlags>::type>(b));
}

CPUFlags operator&(CPUFlags a, Byte b) {
    return static_cast<CPUFlags> (
            static_cast<std::underlying_type<CPUFlags>::type>(a) & b);
}

CPUFlags &operator&=(CPUFlags &a, CPUFlags b) {
    a = static_cast<CPUFlags> (
            static_cast<std::underlying_type<CPUFlags>::type>(a) &
            static_cast<std::underlying_type<CPUFlags>::type>(b)
    );

    return a;
}

Byte &operator&=(Byte &a, CPUFlags b) {
    a &= static_cast<std::underlying_type<CPUFlags>::type>(b);

    return a;
}

CPUFlags operator~(CPUFlags a) {
    return static_cast<CPUFlags> (
            ~static_cast<std::underlying_type<CPUFlags>::type>(a));
}


bool CPU::getFlag(CPUFlags flag) const {
    return (registers.f & flag) == flag;
}

void CPU::setFlag(CPUFlags flag) {
    registers.f |= flag;
}

void CPU::setFlag(CPUFlags flag, bool set) {
    if (set) {
        setFlag(flag);
    } else {
        resetFlag(flag);
    }
}

void CPU::resetFlag(CPUFlags flag) {
    registers.f &= ~flag;
}

}
