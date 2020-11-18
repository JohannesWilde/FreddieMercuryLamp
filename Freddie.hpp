#ifndef Freddie_MERCURY_HPP
#define Freddie_MERCURY_HPP

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
    LedPositionFreddie0 = 3,
    LedPositionFreddie1 = 4,
    LedPositionFreddie2 = 5,
    LedPositionFreddie3 = 6,
    LedPositionWords0 = 7,
    LedPositionWords1 = 8,
    LedPositionWords2 = 9
};

void updateFreddiesRays_(Adafruit_NeoPixel & strip,
                          Color_t const & ray0, Color_t const & ray1, Color_t const & ray2)
{
    strip.setPixelColor(LedPositionRay0, ray0);
    strip.setPixelColor(LedPositionRay1, ray1);
    strip.setPixelColor(LedPositionRay2, ray2);
}


void updateFreddieHimself_(Adafruit_NeoPixel & strip,
                            Color_t const & Freddie0, Color_t const & Freddie1, Color_t const & Freddie2, Color_t const & Freddie3)
{
    strip.setPixelColor(LedPositionFreddie0, Freddie0);
    strip.setPixelColor(LedPositionFreddie1, Freddie1);
    strip.setPixelColor(LedPositionFreddie2, Freddie2);
    strip.setPixelColor(LedPositionFreddie3, Freddie3);
}


void updateFreddiesWords_(Adafruit_NeoPixel & strip,
                           Color_t const & word0, Color_t const & word1, Color_t const & word2)
{
    strip.setPixelColor(LedPositionWords0, word0);
    strip.setPixelColor(LedPositionWords1, word1);
    strip.setPixelColor(LedPositionWords2, word2);

}

} // anonymous namespace

namespace Freddie
{

void lightUpFreddie(Adafruit_NeoPixel & strip,
                     Color_t const & ray0, Color_t const & ray1, Color_t const & ray2,
                     Color_t const & Freddie0, Color_t const & Freddie1, Color_t const & Freddie2, Color_t const & Freddie3,
                     Color_t const & words0, Color_t const & words1, Color_t const & words2)
{
    updateFreddiesRays_(strip, ray0, ray1, ray2);
    updateFreddieHimself_(strip, Freddie0, Freddie1, Freddie2, Freddie3);
    updateFreddiesWords_(strip, words0, words1, words2);
    strip.show();
}

void lightUpFreddie(Adafruit_NeoPixel & strip,
                     Color_t const & rays,
                     Color_t const & Freddies,
                     Color_t const & words)
{
    lightUpFreddie(strip, rays, rays, rays, Freddies, Freddies, Freddies, Freddies, words, words, words);
}


void lightUpFreddiesRays(Adafruit_NeoPixel & strip,
                          Color_t const & ray0, Color_t const & ray1, Color_t const & ray2)
{
    updateFreddiesRays_(strip, ray0, ray1, ray2);
    strip.show();
}


void lightUpFreddiesRays(Adafruit_NeoPixel & strip,
                          Color_t const & rays)
{
    lightUpFreddiesRays(strip, rays, rays, rays);
}


void lightUpFreddieHimself(Adafruit_NeoPixel & strip,
                            Color_t const & Freddie0, Color_t const & Freddie1, Color_t const & Freddie2, Color_t const & Freddie3)
{
    updateFreddieHimself_(strip, Freddie0, Freddie1, Freddie2, Freddie3);
    strip.show();
}


void lightUpFreddieHimself(Adafruit_NeoPixel & strip,
                            Color_t const & Freddies)
{
    lightUpFreddieHimself(strip, Freddies, Freddies, Freddies, Freddies);
}


void lightUpFreddiesWords(Adafruit_NeoPixel & strip,
                           Color_t const & word0, Color_t const & word1, Color_t const & word2)
{
    updateFreddiesWords_(strip, word0, word1, word2);
    strip.show();
}


void lightUpFreddiesWords(Adafruit_NeoPixel & strip,
                           Color_t const & words)
{
    lightUpFreddiesWords(strip, words, words, words);
}

} // namespace Freddie

#endif // Freddie_MERCURY_HPP
