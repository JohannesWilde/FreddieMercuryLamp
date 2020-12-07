#include "Colors.hpp"

#include <Adafruit_NeoPixel.h>

namespace // anonymous namespace
{
inline uint8_t scaleColorPart(uint8_t const input, double const & scaleFactor)
{
    // this uses approximately 1200 bytes of flash storage!
    return static_cast<uint8_t>(static_cast<double>(input) * scaleFactor);
}
} // anonymous namespace

namespace Colors
{

Color_t colorScaleBrightness(Color_t const & input, double const & scaleFactor)
{
    return Adafruit_NeoPixel::Color(scaleColorPart(input >> 16, scaleFactor),
                                    scaleColorPart(input >> 8, scaleFactor),
                                    scaleColorPart(input >> 0, scaleFactor),
                                    scaleColorPart(input >> 24, scaleFactor));
}

}
