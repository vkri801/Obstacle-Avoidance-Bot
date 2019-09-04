/*! \file
    \brief Provides the MPU class.
    \see MPU
*/

#ifndef MPU_H
#define MPU_H

#include "MPU9250.h"
#include "quaternionFilters.h"

#include "Filter.h"
#include "Integrator.h"
#include "Differentiator.h"

/// Wrapper class around the FaBo9Axis MPU.
/**
Provides an interface to the acceleration readings from the MPU, as well as
a calculation of the velocity and position using numerical integration.
*/
class MPU
{
    float heading_offset;

    public:

    /// Initialises filters on the MPU readings.
    /**
    Makes the assumption that it is starting with 0 orientation and
    acceleration, and measures the current readings from the MPU to use as
    offsets in later readouts.

    \note If the MPU is not connected this function will hang.
    
    \note If the MPU startup (`mpu.begin()`) fails, this function will hang.
    */
    MPU();

    /// Updates the acceleration, velocity, position and orientation
    /// with data from the MPU.
    /**
    This should be called repeatedly, as a task in the main loop.

    \see main.ino
    */
    void update();

    /// Get acceleration data
    /**
    \note Checks for NULL inputs, so put zero for outputs you don't care about.
    */
    void accel(float* ax, float* ay, float* az);

    /// Get gyro data
    /**
    \note Checks for NULL inputs, so put zero for outputs you don't care about.
    */
    void gyro(float* ax, float* ay, float* az);

    /// Get magnetometer data
    /**
    \note Checks for NULL inputs, so put zero for outputs you don't care about.
    */
    float mag();

    /// Get heading
    /**
    */
    float heading();

    void reset_heading();
};

#endif

