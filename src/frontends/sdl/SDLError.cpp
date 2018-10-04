#include "SDLError.hpp"

#include <SDL.h>

namespace nsfgbe {

SDLError::SDLError(std::string const &message) :
        runtime_error(message + ": " + SDL_GetError()) {
}

}
