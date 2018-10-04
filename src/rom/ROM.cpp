#include "ROM.hpp"

#include <fstream>

namespace nsfgbe {

ROM::ROM(const char *path) {
    std::ifstream ifs(path, std::ios::binary | std::ios::ate);
    std::ifstream::pos_type pos = ifs.tellg();

    std::vector<char> result(static_cast<unsigned long>(pos));

    ifs.seekg(0, std::ios::beg);
    ifs.read(&result[0], pos);

    for (char i : result) {
        buffer.push_back(static_cast<Byte>(i));
    }
}

ROM::ROM(const Byte *buffer, size_t length) :
        buffer(buffer, buffer + length) {
}

const std::vector<Byte> &ROM::getBuffer() const {
    return buffer;
}

std::string ROM::getTitle() const {
    std::string title;
    size_t index = 0x134;
    while (buffer[index] != 0) {
        title.push_back(buffer[index]);
        ++index;
    }

    return title;
}

ROM::ROMType ROM::getROMType() const {
    return static_cast<ROMType>(buffer[0x147]);
}

ROM::RAMSize ROM::getRAMSize() const {
    return static_cast<RAMSize>(buffer[0x149]);
}

}
