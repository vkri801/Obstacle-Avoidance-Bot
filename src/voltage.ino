/*! \file
    \brief Prints out the battery voltage to serial.
*/

#ifdef VOLTAGE

#include "Battery.h"

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    Serial.print(2 * Battery::voltage(), 6);
    Serial.print(" volts\n");
}

#endif
