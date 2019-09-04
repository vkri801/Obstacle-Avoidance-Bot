/*! \file
    \brief Collection of declarations for interfacing with the robot.

This file declares a namespace, Robot, which has declarations for the sensors
as they are found in main.ino.

If you are writing a new state machine, you will probably want this file `#includ`ed
at the top, since it provides references to all of the sensors/actuators.

\see Robot
\see PathFinding
\see ObstacleAvoidance
\see FireFighting
\see main.ino

You might also want to see uses of this namespace in action:

\see PathFinding.cpp
\see ObstacleAvoidance.cpp
\see FireFighting.cpp
*/

#ifndef ROBOT_H
#define ROBOT_H

#include "Sonar.h"
#include "MotorController.h"
#include "IRSensor.h"
#include "Firehose.h"
#include "MPU.h"

namespace Robot
{
    extern void (*current_state)(void);

    extern Sonar* sonar; 

    extern MotorController* motor_controller; 

    extern IRSensor* ir_port_bow; 
    extern IRSensor* ir_star_bow; 
    extern IRSensor* ir_port;     
    extern IRSensor* ir_star;     

    extern MPU* mpu;

    extern Firehose* firehose; 
}

#endif
