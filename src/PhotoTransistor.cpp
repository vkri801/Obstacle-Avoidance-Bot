/*! \file
    \brief Implementation of the PhotoTransistor class.
    \see PhotoTransistor
*/

#include "PhotoTransistor.h"
#include <Arduino.h>

PhotoTransistor::PhotoTransistor(int pin) : pin(pin)
{
    pinMode(pin, INPUT);
}

int PhotoTransistor::read_raw()
{
    return analogRead(this->pin);
}

