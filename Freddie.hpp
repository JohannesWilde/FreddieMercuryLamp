#ifndef Freddie_MERCURY_HPP
#define Freddie_MERCURY_HPP

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include "Colors.hpp"

using namespace Colors;

namespace // anonymous
{

#ifdef DEVELOPMENT_SETUP
// For development board
enum LedPositions
{
    LedPositionRayLeftRight = 1,
    LedPositionRayLeftLeft = 0,
    LedPositionRayCenterRight = 3,
    LedPositionRayCenterLeft = 2,
    LedPositionRayRightRight = 5,
    LedPositionRayRightLeft = 4,
    LedPositionFreddieLegLeft = 6,
    LedPositionFreddieLegRight = 7,
    LedPositionFreddieStomach = 8,
    LedPositionFreddieArmRight = 11,
    LedPositionFreddieArmLeft = 9,
    LedPositionFreddieChest = 10,
    LedPositionWords0 = 12,
    LedPositionWords1 = 13,
    LedPositionWords2 = 14,
    LedsCount = 15
};

#else // DEVELOPMENT_SETUP

enum LedPositions
{
    LedPositionRayLeftRight = 13,
    LedPositionRayLeftLeft = 14,
    LedPositionRayCenterRight = 10,
    LedPositionRayCenterLeft = 11,
    LedPositionRayRightRight = 7,
    LedPositionRayRightLeft = 8,
    LedPositionFreddieLegLeft = 4,
    LedPositionFreddieLegRight = 3,
    LedPositionFreddieStomach = 5,
    LedPositionFreddieArmRight = 6,
    LedPositionFreddieArmLeft = 12,
    LedPositionFreddieChest = 9,
    LedPositionWords0 = 0,
    LedPositionWords1 = 1,
    LedPositionWords2 = 2,
    LedsCount = 15
};

#endif // DEVELOPMENT_SETUP

void updateFreddiesRays_(Adafruit_NeoPixel & strip,
                          Color_t const & ray0, Color_t const & ray1, Color_t const & ray2)
{
    strip.setPixelColor(LedPositionRayLeftRight, ray0);
    strip.setPixelColor(LedPositionRayLeftLeft, ray0);
    strip.setPixelColor(LedPositionRayCenterRight, ray1);
    strip.setPixelColor(LedPositionRayCenterLeft, ray1);
    strip.setPixelColor(LedPositionRayRightRight, ray2);
    strip.setPixelColor(LedPositionRayRightLeft, ray2);
}


void updateFreddieHimself_(Adafruit_NeoPixel & strip,
                            Color_t const & Freddie0, Color_t const & Freddie1, Color_t const & Freddie2, Color_t const & Freddie3)
{
    strip.setPixelColor(LedPositionFreddieLegLeft, Freddie0);
    strip.setPixelColor(LedPositionFreddieLegRight, Freddie0);
    strip.setPixelColor(LedPositionFreddieStomach, Freddie1);
    strip.setPixelColor(LedPositionFreddieChest, Freddie2);
    strip.setPixelColor(LedPositionFreddieArmRight, Freddie3);
    strip.setPixelColor(LedPositionFreddieArmLeft, Freddie3);
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

void lightUpFreddie(Adafruit_NeoPixel & strip,
                     Color_t const & everything)
{
    lightUpFreddie(strip, /*rays*/ everything, /*Freddies*/ everything, /*words*/ everything);
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
