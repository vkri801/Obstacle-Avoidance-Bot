/*! \file
    \brief Implementation of Battery functions.
    \see Battery
*/

#include "Battery.h"

#include <Arduino.h>

#include "utils.h"

bool Battery::ok()
{
    static char low_voltage_count;

    int raw_lipo = analogRead(A0);

    // 3.5V (discharged) = 717(3.5V Min)
    //
    // Battery voltage should never drop below 3V, so 3.5 is a safety factor.
    if (raw_lipo < 717)
    {
        // battery might not be ok, record the occurence.
        low_voltage_count++;

        // has reported low voltage many times, battery might not be ok.
        if (low_voltage_count > 5)
        {
            serlog("LOW BATTERY\n");
            return false;
        }
    }

    else
    {
        // battery is ok
        low_voltage_count = 0;
    }

    return true;
}

float Battery::voltage()
{
    return 5.0 * (analogRead(A0) / 1024.0);
}

