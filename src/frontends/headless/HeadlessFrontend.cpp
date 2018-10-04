#include "HeadlessFrontend.hpp"

namespace gb {

bool HeadlessFrontend::isRunning() const {
    return running;
}

void HeadlessFrontend::setRunning(bool running) {
    HeadlessFrontend::running = running;
}

void HeadlessFrontend::update() {}

void HeadlessFrontend::beforeSurfaceUpdate() {}

uint32_t *HeadlessFrontend::getPixelBuffer() {
    return pixels.data();
}

void HeadlessFrontend::afterSurfaceUpdate() {}

void HeadlessFrontend::render() {}

void HeadlessFrontend::postRender() {}

bool HeadlessFrontend::isPressed(InputHandler::Key key) const {
    return false;
}

}
