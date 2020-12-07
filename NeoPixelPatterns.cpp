#include "NeoPixelPatterns.hpp"

namespace NeoPixelPatterns
{

double brightnessFunctionMountain(const double x)
{
    double constexpr halfWidthHalfMaximum = 2.;
    double constexpr halfWidthHalfMaximumSqrt = sqrt(halfWidthHalfMaximum);
    double constexpr normalization = 2. * atan(1./(2 * halfWidthHalfMaximumSqrt));
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

void updateStripWrapping(uint32_t * pixelsPointer, uint8_t const numberOfPixels,
                         BrightnessFunctionType brightnessFunction,
                         Colors::Color_t const &color, double const & currentTime)
{
    double const numberOfPixelsDouble = static_cast<double>(numberOfPixels);
    double previousBrightness = brightnessFunction(symmetrizePosition(0 - currentTime, numberOfPixelsDouble) - .5);
    for (unsigned i=0; i < numberOfPixels; ++i, ++pixelsPointer)
    {
        double const normalizedPosition = symmetrizePosition(i - currentTime, numberOfPixelsDouble);
        double const nextBrightness = brightnessFunction(normalizedPosition+.5);
        // Where the brightness wraps around, previousBrightness has to be recalculated.
        if (nextBrightness < previousBrightness)
        {
            previousBrightness = brightnessFunction(normalizedPosition-.5);
        }

        // As written above: brightness = F(i+.5) - F(i-.5)
        double const brightness = nextBrightness - previousBrightness;

        *pixelsPointer = Colors::colorScaleBrightness(color, brightness);

        previousBrightness = nextBrightness;
    }
}

void updateStripOffset(uint32_t * pixelsPointer, uint8_t const numberOfPixels,
                       BrightnessFunctionType brightnessFunction,
                       Colors::Color_t const &color, double const & currentTime)
{
    // subtract 1 here, as the position should be in (0, N-1) for N pixels
    double const offsetPosition = circlePosition(currentTime, static_cast<double>(numberOfPixels - 1));
    double previousBrightness = brightnessFunction(0 - offsetPosition - .5);
    for (unsigned i=0; i < numberOfPixels; ++i, ++pixelsPointer)
    {
        double const normalizedPosition = (i - offsetPosition);
        double const nextBrightness = brightnessFunction(normalizedPosition+.5);
        // As written above: brightness = F(i+.5) - F(i-.5)
        double const brightness = nextBrightness - previousBrightness;

        *pixelsPointer = Colors::colorScaleBrightness(color, brightness);

        previousBrightness = nextBrightness;
    }
}

} // NeoPixelPatterns
