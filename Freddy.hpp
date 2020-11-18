#ifndef FREDDY_MERCURY_HPP
#define FREDDY_MERCURY_HPP

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include "Colors.hpp"

using namespace Colors;

namespace // anonymous
{

enum LedPositions
{
    LedPositionRay0 = 0,
    LedPositionRay1 = 1,
    LedPositionRay2 = 2,
    LedPositionFreddy0 = 3,
    LedPositionFreddy1 = 4,
    LedPositionFreddy2 = 5,
    LedPositionFreddy3 = 6,
    LedPositionWords0 = 7,
    LedPositionWords1 = 8,
    LedPositionWords2 = 9
};

void updateFreddysRays_(Adafruit_NeoPixel & strip,
                          Color_t const & ray0, Color_t const & ray1, Color_t const & ray2)
{
    strip.setPixelColor(LedPositionRay0, ray0);
    strip.setPixelColor(LedPositionRay1, ray1);
    strip.setPixelColor(LedPositionRay2, ray2);
}


void updateFreddyHimself_(Adafruit_NeoPixel & strip,
                            Color_t const & freddy0, Color_t const & freddy1, Color_t const & freddy2, Color_t const & freddy3)
{
    strip.setPixelColor(LedPositionFreddy0, freddy0);
    strip.setPixelColor(LedPositionFreddy1, freddy1);
    strip.setPixelColor(LedPositionFreddy2, freddy2);
    strip.setPixelColor(LedPositionFreddy3, freddy3);
}


void updateFreddysWords_(Adafruit_NeoPixel & strip,
                           Color_t const & word0, Color_t const & word1, Color_t const & word2)
{
    strip.setPixelColor(LedPositionWords0, word0);
    strip.setPixelColor(LedPositionWords1, word1);
    strip.setPixelColor(LedPositionWords2, word2);

}

} // anonymous namespace

namespace Freddy
{

void lightUpFreddy(Adafruit_NeoPixel & strip,
                   Color_t const & ray0, Color_t const & ray1, Color_t const & ray2,
                   Color_t const & freddy0, Color_t const & freddy1, Color_t const & freddy2, Color_t const & freddy3,
                   Color_t const & words0, Color_t const & words1, Color_t const & words2)
{
    updateFreddysRays_(strip, ray0, ray1, ray2);
    updateFreddyHimself_(strip, freddy0, freddy1, freddy2, freddy3);
    updateFreddysWords_(strip, words0, words1, words2);
    strip.show();
}

void lightUpFreddy(Adafruit_NeoPixel & strip,
                   Color_t const & rays,
                   Color_t const & freddys,
                   Color_t const & words)
{
    lightUpFreddy(strip, rays, rays, rays, freddys, freddys, freddys, freddys, words, words, words);
}


void lightUpFreddysRays(Adafruit_NeoPixel & strip,
                        Color_t const & ray0, Color_t const & ray1, Color_t const & ray2)
{
    updateFreddysRays_(strip, ray0, ray1, ray2);
    strip.show();
}


void lightUpFreddysRays(Adafruit_NeoPixel & strip,
                        Color_t const & rays)
{
    lightUpFreddysRays(strip, rays, rays, rays);
}


void lightUpFreddyHimself(Adafruit_NeoPixel & strip,
                          Color_t const & freddy0, Color_t const & freddy1, Color_t const & freddy2, Color_t const & freddy3)
{
    updateFreddyHimself_(strip, freddy0, freddy1, freddy2, freddy3);
    strip.show();
}


void lightUpFreddyHimself(Adafruit_NeoPixel & strip,
                          Color_t const & freddys)
{
    lightUpFreddyHimself(strip, freddys, freddys, freddys, freddys);
}


void lightUpFreddysWords(Adafruit_NeoPixel & strip,
                         Color_t const & word0, Color_t const & word1, Color_t const & word2)
{
    updateFreddysWords_(strip, word0, word1, word2);
    strip.show();
}


void lightUpFreddysWords(Adafruit_NeoPixel & strip,
                         Color_t const & words)
{
    lightUpFreddysWords(strip, words, words, words);
}

} // namespace Freddy

#endif // FREDDY_MERCURY_HPP
