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

double normalizePosition(const double position, const double range)
{
    return fmod(fmod(position, range) + range, range) - (range / 2.);
}



} // NeoPixelPatterns
