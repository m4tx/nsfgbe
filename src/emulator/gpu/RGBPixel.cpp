#include "RGBPixel.hpp"

namespace gb {

uint32_t RGBPixel::toRGB() const {
    return (r << 16) | (g << 8) | (b << 0);
}

}
