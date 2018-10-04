#include <iostream>

#include "SDLFrontend.hpp"
#include "SDLError.hpp"

namespace nsfgbe {

SDLFrontend::SDLFrontend() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw SDLError("SDL could not be initialized");
    }

    window = SDL_CreateWindow(
            "NSFGBE",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH, WINDOW_HEIGHT,
            SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        throw SDLError("Window could not be created");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    renderTexture = SDL_CreateTexture(
            renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
            SCREEN_WIDTH, SCREEN_HEIGHT);
}

SDLFrontend::~SDLFrontend() {
    SDL_DestroyWindow(window);
    window = nullptr;
    SDL_Quit();
}

bool SDLFrontend::isRunning() const {
    return !quit;
}

void SDLFrontend::update() {
    startTicks = SDL_GetTicks();

    SDL_Event e{};
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        }
    }

    keyStates = SDL_GetKeyboardState(nullptr);
}

bool SDLFrontend::isPressed(SDLFrontend::Key key) const {
    return keyStates[KEY_MAP[key]] != 0;
}

void SDLFrontend::beforeSurfaceUpdate() {
}

uint32_t *SDLFrontend::getPixelBuffer() {
    return pixels.data();
}

void SDLFrontend::afterSurfaceUpdate() {
    void *pixelBuffer = nullptr;
    int pitch = 0;
    SDL_LockTexture(renderTexture, nullptr, &pixelBuffer, &pitch);
    memcpy(pixelBuffer, pixels.data(),
           SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(uint32_t));
    SDL_UnlockTexture(renderTexture);
}

void SDLFrontend::render() {
    SDL_Rect stretchRect;
    stretchRect.x = 0;
    stretchRect.y = 0;
    stretchRect.w = WINDOW_WIDTH;
    stretchRect.h = WINDOW_HEIGHT;

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, renderTexture, nullptr, &stretchRect);
    SDL_RenderPresent(renderer);
}

void SDLFrontend::postRender() {
    Uint32 frameTicks = SDL_GetTicks() - startTicks;
    if (frameTicks < SCREEN_TICKS_PER_FRAME) {
        SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
    }
}

}
