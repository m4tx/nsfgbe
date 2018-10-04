#ifndef GAMEBOY_EMULATOR_SDLERROR_H
#define GAMEBOY_EMULATOR_SDLERROR_H


#include <stdexcept>
#include <string>

namespace gb {

class SDLError : public std::runtime_error {
public:
    explicit SDLError(std::string const &message);
};

}


#endif //GAMEBOY_EMULATOR_SDLERROR_H
