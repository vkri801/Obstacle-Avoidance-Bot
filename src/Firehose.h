/*! \file
    \brief Declaration of the Firehose class.
    \see Firehose
*/

#ifndef FIREHOSE_H
#define FIREHOSE_H

#include <Servo.h>

#include "PhotoTransistor.h"

/// Control of the fan and servo that it's mounted to.
/**
This class provides an interface for controlling the fan and the
servo that it's mounted to.

It provides functions for automatically tracking fires that are in front
of the robot.

\see FireFighting
\see PhotoTransistor
*/
class Firehose
{
    PhotoTransistor port;
    PhotoTransistor star;

    int fan_pin;

    int servo_pos;
    Servo servo;

    public:

    Firehose();
    ~Firehose();

    /// Returns `true` if a fire is detected in front of the robot.
    /**
    This is done by checking if the reading from either phototransistor is above
    a certain threshold.
    
    \see FIREHOSE_FIRE_DETECTION_THRESHOLD
    */
    bool fire_detected();
    
    /// Rotates the fan so that is is facing the fire.
    /**
    Tracking is done by Proportional control over the difference between the
    readings from the phototransistors.

    Returns true once the fan is facing the fire.

    \see FIREHOSE_FAN_FACING_FIRE_THRESHOLD
    */
    bool track_fire(); 

    void on();  ///< Turns on the fan.
    void off(); ///< Turns off the fan.

    /// Resets the position of the servo.
    /**
    Makes the fan point straight ahead again. It's important to do this
    once a fire has been put out, since the phototransistors are quite 
    directional, and might not "see" any later fires if the fan is not
    pointing straight ahead.
    */
    void reset_servo_pos();
};

#endif
