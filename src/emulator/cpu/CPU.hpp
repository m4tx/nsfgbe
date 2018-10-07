#ifndef GAMEBOY_EMULATOR_CPU_H
#define GAMEBOY_EMULATOR_CPU_H


#include "Types.hpp"

namespace nsfgbe {

struct Registers {
    union {
        struct {
            Byte f = 0xB0;
            Byte a = 0x01;
        };
        Word af;
    };
    union {
        struct {
            Byte c;
            Byte b;
        };
        Word bc = 0x0013;
    };
    union {
        struct {
            Byte e;
            Byte d;
        };
        Word de = 0x00D8;
    };
    union {
        struct {
            Byte l;
            Byte h;
        };
        Word hl = 0x014D;
    };

    Word sp = 0xFFFE;
    Word pc = 0x0100;
};


enum class CPUFlags : Byte {
    ZERO = 1 << 7,
    SUBTRACT = 1 << 6,
    HALF_CARRY = 1 << 5,
    CARRY = 1 << 4,
    ALL_FLAGS = ZERO | SUBTRACT | HALF_CARRY | CARRY,
};

CPUFlags operator|(CPUFlags a, CPUFlags b);

CPUFlags &operator|=(CPUFlags &a, CPUFlags b);

Byte &operator|=(Byte &a, CPUFlags b);

CPUFlags operator&(CPUFlags a, CPUFlags b);

CPUFlags operator&(Byte a, CPUFlags b);

CPUFlags operator&(CPUFlags a, Byte b);

CPUFlags &operator&=(CPUFlags &a, CPUFlags b);

Byte &operator&=(Byte &a, CPUFlags b);

CPUFlags operator~(CPUFlags a);


class CPU {
public:
    Registers registers;
    bool halted = false;

    bool getFlag(CPUFlags flag) const;

    void setFlag(CPUFlags flag);

    void setFlag(CPUFlags flag, bool set);

    void resetFlag(CPUFlags flag);
};

}


#endif //GAMEBOY_EMULATOR_CPU_H
