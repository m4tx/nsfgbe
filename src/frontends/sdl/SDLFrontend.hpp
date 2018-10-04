#ifndef GAMEBOY_EMULATOR_SDLFRONTEND_H
#define GAMEBOY_EMULATOR_SDLFRONTEND_H


#include <atomic>
#include <array>
#include <SDL.h>

#include <emulator/Constants.hpp>
#include <frontends/Frontend.hpp>

namespace nsfgbe {

class SDLFrontend : public Frontend {
private:
    const unsigned WINDOW_WIDTH = SCREEN_WIDTH * 6;
    const unsigned WINDOW_HEIGHT = SCREEN_HEIGHT * 6;
    const unsigned FPS_CAP = 60;
    const unsigned SCREEN_TICKS_PER_FRAME = 1000 / FPS_CAP;

    SDL_Window *window = nullptr;

    SDL_Renderer *renderer;
    SDL_Texture *renderTexture;
    std::array<uint32_t, SCREEN_WIDTH * SCREEN_HEIGHT> pixels;

    const Uint8 *keyStates;
    Uint32 startTicks;

    bool quit = false;

    const std::array<Uint8, 8> KEY_MAP{
            SDL_SCANCODE_RIGHT,
            SDL_SCANCODE_LEFT,
            SDL_SCANCODE_UP,
            SDL_SCANCODE_DOWN,
            SDL_SCANCODE_X,
            SDL_SCANCODE_Z,
            SDL_SCANCODE_RSHIFT,
            SDL_SCANCODE_RETURN,
    };

public:
    SDLFrontend();

    ~SDLFrontend();

    bool isRunning() const override;

    void update() override;

    bool isPressed(Key key) const override;

    void beforeSurfaceUpdate() override;

    uint32_t *getPixelBuffer() override;

    void afterSurfaceUpdate() override;

    void render() override;

    void postRender() override;
};

}


#endif //GAMEBOY_EMULATOR_SDLFRONTEND_H
