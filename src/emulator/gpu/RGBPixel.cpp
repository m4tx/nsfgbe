#include "RGBPixel.hpp"

namespace nsfgbe {

uint32_t RGBPixel::toRGB() const {
    return (r << 16) | (g << 8) | (b << 0);
}

}
