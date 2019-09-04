/*! \file
    \brief Provides the MotorController class.
    \see MotorController
*/

#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include <Servo.h>

/// Provides open-loop control of the motors.
/**
Sends servo commands to the 4 motors to control the direction of travel.
*/
class MotorController
{
    // the current speed
    int speed_val;

    Servo fl;  // Front Left
    Servo fr;  // Front Right
    Servo rl;  // Rear Left
    Servo rr;  // Rear Right

    // writes micros to the servos
    void write_speed(int lf, int lr, int rr, int rf);
    
    public:

    /// Default constructor.
    /**
    Sets pin modes and attaches servos.
    */
    MotorController();
    
    /// Destructor.
    /**
    Sets pin modes to INPUT and detaches servos.
    */
    ~MotorController();

    /// Sets the speed of the robot.
    /**
    \param speed_val The speed to set for the robot. This should be a number
    in the range +/- 200. Values outside this range are coerced.

    \see PARAMETERS.h to configure the maximum speed_val.
    */
    void set_speed(int speed_val);
    
    /// Stops the robot.
    /**
    */
    void stop();

    /// Command the robot to go forward.
    /**
    */
    void forward();

    /// Command the robot to go in reverse.
    /**
    */
    void reverse();

    /// Command the robot to spin counter-clockwise.
    /**
    */
    void ccw();

    /// Command the robot to spin clockwise.
    /**
    */
    void cw();

    /// Command the robot to strafe to the left.
    /**
    */
    void strafe_left();

    /// Command the robot to strafe to the right.
    /**
    */
    void strafe_right();

};

#endif

