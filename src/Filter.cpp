/*! \file
    \brief Implementation of the Filter class.
    \see Filter
*/

#include "Filter.h"

#include <Arduino.h>

Filter::Filter(float alpha)
{
    this->alpha = alpha;
    this->s1 = 0;
}

float Filter::update(float s0)
{
    this->s1 = this->alpha * s0 + (1-this->alpha) * this->s1;
    return this->s1;
}

float Filter::value()
{
    return this->s1;
}

