/*! \file Battery.h
    \brief Provides the Battery namespace.
    \see Battery
*/

#ifndef BATTERY_H
#define BATTERY_H

/// Contains functions concerning the battery.
/**
At the moment, this only contains one function: `ok()`.
*/
namespace Battery
{
    /// Returns true if the battery is ok.
    /**
    Checks if the battery voltage is more than 3.5 Volts. The battery is a
    LiPo so it's important that the battery is kept within it's limits.

    \return bool: Whether or not the battery is ok.

    \warning Do not let the battery run down below 3V. This function returns
    false when the voltage is less than 3.5V, for some safety factor. If the
    robot stops, and won't start again even when power-cycled, this could be 
    one of the reasons for it! Check the battery's voltage with a multimeter
    before continuing.
    */
    bool ok();

    /// Returns the battery voltage
    /**
    */
    float voltage();
}

#endif
