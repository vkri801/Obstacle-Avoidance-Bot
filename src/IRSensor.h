/*! \file IRSensor.h
    \brief Provides the IRSensor class.
    \see IRSensor
*/

#ifndef IR_SENSOR_H
#define IR_SENSOR_H

#include "Filter.h"

/// Represents an IR sensor.
/**
*/
class IRSensor
{
    int pin;

    public:

    /// Initialises a sensor of the given type on the given pin.
    /**
    \see PIN_DEFINES.h
    */
    IRSensor(int pin);

    /// Returns the raw analogRead reading from this sensor.
    /**
    */
    int read_raw();

    /// Returns the number of cm from this sensor.
    /**
    */
    float read_cm();
};

#endif
