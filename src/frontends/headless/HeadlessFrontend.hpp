#ifndef GAMEBOY_EMULATOR_HEADLESSFRONTEND_H
#define GAMEBOY_EMULATOR_HEADLESSFRONTEND_H


#include <array>

#include <frontends/Frontend.hpp>
#include <emulator/Constants.hpp>

namespace gb {

class HeadlessFrontend : public Frontend {
private:
    std::array<uint32_t, SCREEN_WIDTH * SCREEN_HEIGHT> pixels{};
    bool running = true;

public:
    bool isRunning() const override;

    void setRunning(bool running);

    void update() override;

    void beforeSurfaceUpdate() override;

    uint32_t *getPixelBuffer() override;

    void afterSurfaceUpdate() override;

    void render() override;

    void postRender() override;

    bool isPressed(Key key) const override;
};

}


#endif //GAMEBOY_EMULATOR_HEADLESSFRONTEND_H
