#ifndef GAMEBOY_EMULATOR_FRONTEND_H
#define GAMEBOY_EMULATOR_FRONTEND_H


#include <cstdint>

#include "InputHandler.hpp"

namespace gb {

class Frontend : public InputHandler {
public:
    virtual bool isRunning() const = 0;

    virtual void update() = 0;

    virtual void beforeSurfaceUpdate() = 0;

    virtual uint32_t *getPixelBuffer() = 0;

    virtual void afterSurfaceUpdate() = 0;

    virtual void render() = 0;

    virtual void postRender() = 0;
};

}


#endif //GAMEBOY_EMULATOR_FRONTEND_H
