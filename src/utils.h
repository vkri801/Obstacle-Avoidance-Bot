/*! \file
    \brief Provides some utility functions.
    \see Utils
*/

#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>

#include "PARAMETERS.h"

/// Pointer to the serial com.
/**
*/
extern HardwareSerial* SerialCom;

// Conditional logging.
#ifdef LOG
#define serlog(...) SerialCom->print(__VA_ARGS__)
#else
#define serlog(...)
#endif

/// Provides some utility functions.
/**
*/
namespace Utils
{
    /// Like `micros()`, but in seconds.
    /**
    \note `micros()` will overflow after about 70 minutes.
    */
    float seconds();

    /// Coerces val to between lower and upper
    /**
    \note Lower should be less than upper.
    */
    float coerce(float val, float lower, float upper);

    /// Linear interpolation of x between (x0,x1) and (y0,y1)
    /**
    */
    float lerp(float x, float x0, float x1, float y0, float y1);
}

#include "json.h"

#endif

