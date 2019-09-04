/*! \file
    \brief Implementation of the utility functions.
    \see Utils
*/

#include <Arduino.h>
#include "utils.h"

float Utils::seconds()
{
    return micros() / 1000000.0;
}

float Utils::coerce(float val, float lower, float upper)
{
    if (val < lower) return lower;
    if (val > upper) return upper;
    return val;
}

float Utils::lerp(float x, float x0, float x1, float y0, float y1)
{
    return ( (y0 * (x1 - x)) + (y1 * (x - x0)) ) / (x1 - x0);
}

