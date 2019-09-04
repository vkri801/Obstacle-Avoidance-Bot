/*! \file
    \brief Implementation of the IRSensor class.
    \see IRSensor
*/

#include "IRSensor.h"

#include <Arduino.h>

#include "PARAMETERS.h"

#include "utils.h"


IRSensor::IRSensor(int pin) :
    pin(pin)
{
    serlog("ir init\n");

    pinMode(pin, INPUT);
}


int IRSensor::read_raw()
{
    return analogRead(this->pin);
}


float IRSensor::read_cm()
{
    return (13.0 * 1024.0) / (5.0 * this->read_raw());
}
