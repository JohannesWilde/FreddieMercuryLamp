#ifndef COLORS_HPP
#define COLORS_HPP

#include <Arduino.h>

namespace Colors
{

typedef uint32_t Color_t;

/* copied from Adafruid_NeoPixel - made constexpr as to minimize flash usage */
constexpr Color_t Color(uint8_t r, uint8_t g, uint8_t b, uint8_t w)
{
    return ((Color_t)w << 24) | ((Color_t)r << 16) | ((Color_t)g <<  8) | (Color_t)b;
}

Color_t constexpr Black = Color(0, 0, 0, 0);
Color_t constexpr Red = Color(255, 0, 0, 0);
Color_t constexpr Green = Color(0, 255, 0, 0);
Color_t constexpr Blue = Color(0, 0, 255, 0);
Color_t constexpr Yellow = Color(255, 246, 0, 0);
Color_t constexpr White = Color(0, 0, 0, 255);

Color_t colorScaleBrightness(Color_t const & input, double const & scaleFactor);

}

#endif // COLORS_HPP
