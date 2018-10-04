#include "SDLError.hpp"

#include <SDL.h>

namespace gb {

SDLError::SDLError(std::string const &message) :
        runtime_error(message + ": " + SDL_GetError()) {
}

}
