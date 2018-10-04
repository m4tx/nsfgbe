#ifndef GAMEBOY_EMULATOR_TYPES_H
#define GAMEBOY_EMULATOR_TYPES_H


#include <cstdint>

namespace nsfgbe {

typedef uint8_t Byte;
typedef int8_t SignedByte;
typedef uint16_t Word;
typedef uint16_t Address;

constexpr Byte operator "" _b(unsigned long long value) {
    return static_cast<Byte>(value);
}

constexpr Word operator "" _w(unsigned long long value) {
    return static_cast<Word>(value);
}

constexpr Address operator "" _adr(unsigned long long address) {
    return static_cast<Address>(address);
}

}


#endif //GAMEBOY_EMULATOR_TYPES_H
