#ifndef GAMEBOY_EMULATOR_ROM_H
#define GAMEBOY_EMULATOR_ROM_H


#include <cstdint>
#include <vector>
#include <string>

#include "Types.hpp"

namespace nsfgbe {

class ROM {
private:
    std::vector<Byte> buffer;

public:
    enum class ROMType {
        ROM_ONLY = 0,

        ROM_MBC1 = 1,
        ROM_MBC1_RAM = 2,
        ROM_MBC1_RAM_BATT = 3,

        ROM_MBC2 = 5,
        ROM_MBC2_BATT = 6,

        ROM_RAM = 8,
        ROM_RAM_BATT = 9,
    };

    enum class RAMSize {
        SIZE_NONE,
        SIZE_2K,
        SIZE_8K,
        SIZE_32K,
        SIZE_128K,
    };

    explicit ROM(const char *path);

    ROM(const Byte *buffer, size_t length);

    const std::vector<Byte> &getBuffer() const;

    std::string getTitle() const;

    ROMType getROMType() const;

    RAMSize getRAMSize() const;
};

}


#endif //GAMEBOY_EMULATOR_ROM_H
