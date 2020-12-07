#ifndef NEOPIXELPATTERNS_HPP
#define NEOPIXELPATTERNS_HPP

#include <math.h>
#include <Adafruit_NeoPixel.h>


namespace NeoPixelPatterns
{

/**
 * BrightnessFunctionType This type of function shall be used to calculate pixel brightness.
 * Please note, that this does not calculate the brightness of a single pixel value itself,
 * but is supposed to be the analytic integral of the desired color profile.
 * This is so, that for f(x) the pixel brightness of pixel i can be calculated using
 *  brightness(i) = F(i+.5) - F(i-.5),
 * where F(x) is the brightness function [F(x) = int f(x) dx]. Please note that this
 * function should be normalized, so that:
 *  max(brightness(i)) <= 1,
 *  min(brightness(i)) >= 0.
 */
typedef double(*BrightnessFunctionType)(double);

/**
 * @brief brightnessFunctionMountain Integral for f(x) = b/(1 + x^2/a).
 * @param x position
 * @return brightness in [0,1]
 * From normalization 1 != F(.5) - F(-.5) it results:
 *  b = 1/(2*sqrt(a) * atan(1/(2*sqrt(a)))).
 */
double brightnessFunctionMountain(double const x);

// move position to [-range/2, range/2)
double normalizePosition(double const position, double const range);

template<size_t numberOfPixels, BrightnessFunctionType brightnessFunction>
void updateStrip(Adafruit_NeoPixel & strip, uint32_t const &color, double const currentTime)
{
    double const numberOfPixelsDouble = static_cast<double>(numberOfPixels);
    double previousBrightness = brightnessFunction(normalizePosition(0. - currentTime, numberOfPixelsDouble)-.5);
    for(unsigned i=0; i < numberOfPixels; ++i)
    {
        double const normalizedPosition = normalizePosition(static_cast<double>(i) - currentTime, numberOfPixelsDouble);
        double const nextBrightness = brightnessFunction(normalizedPosition+.5);
        // Where the brightness wraps around, previousBrightness has to be recalculated.
        if (nextBrightness < previousBrightness)
        {
            previousBrightness = brightnessFunction(normalizedPosition-.5);
        }

        // As written above: brightness = F(i+.5) - F(i-.5)
        double const brightness = nextBrightness - previousBrightness;

        uint32_t const colorNew = Adafruit_NeoPixel::Color(
                    Adafruit_NeoPixel::gamma8(static_cast<uint8_t>(static_cast<double>(static_cast<uint8_t>(color >> 16)) * brightness)),
                    Adafruit_NeoPixel::gamma8(static_cast<uint8_t>(static_cast<double>(static_cast<uint8_t>(color >> 8)) * brightness)),
                    Adafruit_NeoPixel::gamma8(static_cast<uint8_t>(static_cast<double>(static_cast<uint8_t>(color >> 0)) * brightness)),
                    Adafruit_NeoPixel::gamma8(static_cast<uint8_t>(static_cast<double>(static_cast<uint8_t>(color >> 24)) * brightness)));
        strip.setPixelColor(i, colorNew);

        previousBrightness = nextBrightness;
    }
    strip.show();
}

template<size_t numberOfPixels, BrightnessFunctionType brightnessFunction>
void updateStripLoop(Adafruit_NeoPixel & strip, uint32_t const &color, unsigned long const totalTimeMs)
{
    unsigned long const startTime = millis();
    unsigned long deltaTime = 0;
    while (deltaTime < totalTimeMs)
    {
        unsigned long const curTime = millis();
        deltaTime = (curTime - startTime);
        double const deltaTimeDouble = static_cast<double>(deltaTime) / 500.;
        updateStrip<numberOfPixels, brightnessFunction>(strip, color, deltaTimeDouble);
    }
}

} // NeoPixelPatterns

#endif // NEOPIXELPATTERNS_HPP
