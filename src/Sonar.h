/*! \file
    \brief Provides the Sonar class.
    \see Sonar
*/

#ifndef SONAR_H
#define SONAR_H

#include <Arduino.h>

#include "Filter.h"

/// Represents the Sonar module on the robot.
/**
Provides an interface to the sonar module, allowing you to see the distance
in front of the robot.
*/
class Sonar
{
    static void trigger();

    Filter filter;

    public:

    /// Initialises the Sonar.
    /**
    This just sets the pin modes accordingly.

    \see PIN_DEFINES.h
    */
    Sonar();

    ~Sonar();

    /// Returns the number of centimeters in front of the robot, with caveats.
    /**
    The sonar module works by first listening for a 10us pulse from your
    code. It then sends out an ultrasonic pulse, and waits for the reply.
    Once the reply comes, the sonar module pulls the echo pin high for a 
    length of time that is proportional to the length in front of the robot.

    A couple things can go wrong here;

    * If the Sonar module is not connected properly, or at all, then the code
    will never recieve a response from the sonar module.

    * If the Sonar module somehow misses the echo, then the code will never
    recieve a response from the sonar module.

    \warning This function does not timeout; if either of the above
    conditions is true, then this function will hang. You should really use
    the one below, which has a timeout. This function is provided as a
    convience, since it returns a float directly rather than a bool.
    */
    float read_cm_unchecked();


    /// Returns the number of centimeters in front of the robot.
    /**
    This function will timeout if the response pulse takes too long. The 
    timeout length can be configured in PARAMETERS.h

    \param[out] out; where to store the reading. This value is not written
    to if the sonar reading timeout occurs.

    \return `bool`; true if the sonar measurement was successful, false
    otherwise.

    \see PARAMETERS.h
    */
    bool read_cm_checked(float* out);
};

#endif
