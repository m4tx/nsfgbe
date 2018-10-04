#include "PixelFIFO.hpp"

#include <cassert>

namespace gb {

PixelFIFO::PixelFIFO() = default;

bool PixelFIFO::canRetrievePixel() const {
    return queue.size() > 8;
}

bool PixelFIFO::canAddEightPixels() const {
    return queue.size() <= 8;
}

void PixelFIFO::addEightPixels(const std::array<Pixel, 8> &pixels) {
    assert(canAddEightPixels());

    for (const Pixel &pixel : pixels) {
        queue.push_back(pixel);
    }
}

void PixelFIFO::addSpritePixels(const std::array<Pixel, 8> &pixels) {
    for (size_t i = 0; i < 8; ++i) {
        if (pixels[i].value != 0) {
            queue[i] = pixels[i];
        }
    }
}

Pixel PixelFIFO::retrievePixel() {
    assert(canRetrievePixel());

    Pixel pixel = queue.front();
    queue.pop_front();
    return pixel;
}

void PixelFIFO::dropPixels(Byte amount) {
    assert(queue.size() >= amount);

    for (Byte i = 0; i < amount; ++i) {
        queue.pop_front();
    }
}

void PixelFIFO::clear() {
    queue.clear();
}

}
