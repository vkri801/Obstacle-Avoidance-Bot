/*! \file
    \brief Implementation of the PID class.
    \see PID
*/

#include "PID.h"

#include <Arduino.h>

PID::PID(float kp, float ki, float kd) :
    dedt(),      // Init differentiator
    edt(),       // Init integrator
    kp(kp),      // Init controller gains
    ki(ki),
    kd(kd),
    reference(0) // Init reference to 0.
{
}

float PID::update(float pv)
{
    float error = this->reference - pv;

    float p = this->kp * error;
    float i = this->ki * this->edt.update(error);
    float d = this->kd * this->dedt.update(error);

    return p+i+d;
}

