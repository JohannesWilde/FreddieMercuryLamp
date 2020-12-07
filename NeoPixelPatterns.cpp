#include "NeoPixelPatterns.hpp"

namespace NeoPixelPatterns
{

double brightnessFunctionMountain(const double x)
{
    double const halfWidthHalfMaximum = 2.;
    double const halfWidthHalfMaximumSqrt = sqrt(halfWidthHalfMaximum);
    double const normalization = 2. * atan(1./(2 * halfWidthHalfMaximumSqrt));
    return atan(x/halfWidthHalfMaximumSqrt) / normalization;
}

template<>
double normalizePosition(const double & position, const double & range)
{
    return fmod(fmod(position, range) + range, range);
}

template<>
unsigned normalizePosition(const unsigned & position, const unsigned & range)
{
    return (position % range);
}

template<>
unsigned long normalizePosition(const unsigned long & position, const unsigned long & range)
{
    return (position % range);
}

void updateStrip(uint32_t * pixelsPointer, uint8_t const numberOfPixels,
                 BrightnessFunctionType brightnessFunction,
//                 PositionNormalizationFunctionType positionNormalizationFunction,
                 uint32_t const &color, double const & currentTime)
{
    double const numberOfPixelsDouble = static_cast<double>(numberOfPixels);
    double previousBrightness = brightnessFunction(circlePosition(0 - currentTime, numberOfPixelsDouble) - .5);
    for (unsigned i=0; i < numberOfPixels; ++i, ++pixelsPointer)
    {
        double const normalizedPosition = circlePosition(i - currentTime, numberOfPixelsDouble);
        double const nextBrightness = brightnessFunction(normalizedPosition+.5);
        // Where the brightness wraps around, previousBrightness has to be recalculated.
        if (nextBrightness < previousBrightness)
        {
            previousBrightness = brightnessFunction(normalizedPosition-.5);
        }

        // As written above: brightness = F(i+.5) - F(i-.5)
        double const brightness = nextBrightness - previousBrightness;

        *pixelsPointer = Adafruit_NeoPixel::Color(
                    static_cast<uint8_t>(static_cast<double>(static_cast<uint8_t>(color >> 16)) * brightness),
                    static_cast<uint8_t>(static_cast<double>(static_cast<uint8_t>(color >> 8)) * brightness),
                    static_cast<uint8_t>(static_cast<double>(static_cast<uint8_t>(color >> 0)) * brightness),
                    static_cast<uint8_t>(static_cast<double>(static_cast<uint8_t>(color >> 24)) * brightness));

        previousBrightness = nextBrightness;
    }
}

} // NeoPixelPatterns
