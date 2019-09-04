/*! \file
    \brief Implementation of the Sonar class.
    \see Sonar
*/

#include "Sonar.h"
#include "PIN_DEFINES.h"
#include "PARAMETERS.h"

#include <Arduino.h>

#include "utils.h"

Sonar::Sonar() : filter(SONAR_FILTER_PARAM)
{
    serlog("init sonar\n");

    pinMode(SONAR_TRIG_PIN, OUTPUT);
    pinMode(SONAR_ECHO_PIN, INPUT);
}


Sonar::~Sonar()
{
    pinMode(SONAR_TRIG_PIN, INPUT);
    pinMode(SONAR_ECHO_PIN, INPUT);
}


void Sonar::trigger()
{
    digitalWrite(SONAR_TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(SONAR_TRIG_PIN, LOW);
}


float Sonar::read_cm_unchecked()
{
    Sonar::trigger();

    // wait for reply
    while(digitalRead(SONAR_ECHO_PIN) == 0);

    // measure length of pulse response.
    long t1 = micros();
    while(digitalRead(SONAR_ECHO_PIN) == 1);
    long pulse_width = micros() - t1;

    return this->filter.update(pulse_width / 58.0);
}


bool Sonar::read_cm_checked(float* out)
{
    // Anything over 400 cm (23200 us pulse) is considered out of range.
    static const unsigned int MAX_DIST = 23200;

    long t1, pulse_width;

    Sonar::trigger();

    // Wait for pulse on echo pin
    t1 = micros();
    while (digitalRead(SONAR_ECHO_PIN) == 0)
    {
        // out of range
        if ((micros() - t1) > MAX_DIST) return false;
    }

    // Measure how long the echo pin was held high (pulse width)
    // Note: the micros() counter will overflow after ~70 min
    t1 = micros();
    while (digitalRead(SONAR_ECHO_PIN) == 1)
    {
        // out of range
        if ((micros() - t1) > MAX_DIST) return false;
    }

    pulse_width = micros() - t1;

    // Calculate distance in centimeters. The constant is found in the
    // datasheet, and calculated from the assumed speed of sound in air at sea
    // level (~340 m/s).
    *out = this->filter.update(pulse_width / 58.0);

    return true;
}

