#ifndef GAMEBOY_EMULATOR_CPU_H
#define GAMEBOY_EMULATOR_CPU_H


#include "Types.hpp"

namespace gb {

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

enum CPUFlags {
    FLAG_ZERO = 1 << 7,
    FLAG_SUBTRACT = 1 << 6,
    FLAG_HALF_CARRY = 1 << 5,
    FLAG_CARRY = 1 << 4,
    ALL_FLAGS = FLAG_ZERO | FLAG_SUBTRACT | FLAG_HALF_CARRY | FLAG_CARRY,
};

class CPU {
public:
    Registers registers;
    bool halted = false;

    bool getFlag(Byte flag) const;

    void setFlag(Byte flag);

    void setFlag(Byte flag, bool set);

    void resetFlag(Byte flag);
};

}


#endif //GAMEBOY_EMULATOR_CPU_H
