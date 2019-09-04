/*! \file
    \brief Implementation of the ObstacleAvoidance state machine functions.
    \see ObstacleAvoidance
    \see \ref state_machines
    \see Robot
*/

#include "ObstacleAvoidance.h"
#include <Arduino.h>
#include "Robot.h"

#include "PARAMETERS.h"

#include "FireFighting.h"
#include "PathFinding.h"

#include "MotorController.h"

#include "utils.h"

/// When the avoidance manuveure was started.
///
long AVOIDANCE_STARTED;

/// How long the avoidance manuvre took.
///
long AVOIDANCE_LENGTH;

/// When the forward motion was started.
///
long FORWARD_STARTED;

/// When the recovery was started
///
long RECOVERY_STARTED;

/// Pointer to MotorController member function.
/**
When the robot strafe's around an obstacle, it first saves the movement command
in a pointer of this type.

In English: "The type `MotorControl` is an alias for a pointer to a member
function of the `MotorController` class. The function in question accepts no
arguments and returns nothing."

\see RECOVERY_FP
*/
typedef void (*MotorControl)(void);

/// A pointer to the function to call during recovery. This should either be
/// `motor_controller->strafe_left` or `strafe_right`.
MotorControl RECOVERY_FP;

void strafe_left()
{
    Robot::motor_controller->strafe_left();
}

void strafe_right()
{
    Robot::motor_controller->strafe_right();
}

/// The return pointer, named Bob.
/**
Bob points to the state to move to after obstacle avoidance is complete.

Bob exists because we'd like to reuse the same ObstacleAvoidance code, but coming
from other states. The previous state tells Bob where to point, and then changes
the robot's state into ObstacleAvoidance. When ObstacleAvoidance is complete,
we move into the state pointed to by Bob.
*/
void (*Bob)(void);

void ObstacleAvoidance::set_bob(void (*bob)(void))
{
    Bob = bob;
}

/// Pointer to IR sensor to check during avoidance.
/**
*/
typedef float (*FrontIR)(void);

FrontIR RECOVERY_SENSOR;

float port_ir()
{
    return Robot::ir_port_bow->read_cm();
}

float star_ir()
{
    return Robot::ir_star_bow->read_cm();
}


void ObstacleAvoidance::Start()
{
    serlog("oa start\n");

    // first, check for fire, and move to firefighting state if so.
    if (Robot::firehose->fire_detected())
    {
        serlog("detected fire, moving to firefighting\n");

        Robot::current_state = FireFighting::Start;
        return;
    }

    // pointer to the direction to strafe.
    MotorControl strafe;

    // now read each of the IR sensors on the port and starboard bow.
    // we choose to strafe towards the sensor with the brightest reading.
    if (Robot::ir_port_bow->read_cm() < Robot::ir_star_bow->read_cm())
    {
        serlog("strafing right\n");

        // strafe to the right, recovery to the left.
        // note that `strafe` is just a pointer, we don't actually invoke
        // the movement just yet.
        strafe = strafe_right;
        RECOVERY_FP = strafe_left;
        RECOVERY_SENSOR = port_ir;
    }

    else 
    {
        serlog("strafing left\n");

        // strafe to the left, recovery to the right.
        strafe = strafe_left;
        RECOVERY_FP = strafe_right;
        RECOVERY_SENSOR = star_ir;
    }

    // now actually call the movement function.
    // this is so that the avoidance timer is as close to the beginning
    // of the strafe as possible.
    //
    // The weird syntax is because "pointer to function" is a different
    // type to "pointer to member function", so you need to do some weird
    // shit to get the pointer to dereference properly.
    strafe();
    AVOIDANCE_STARTED = millis();
    Robot::current_state = ObstacleAvoidance::Strafing;
}


void ObstacleAvoidance::Strafing()
{
    // for now, we just stop if there is no room next to the robot to move.
    if (Robot::ir_port->read_cm() < OBSTACLE_AVOIDANCE_STRAFE_TOO_CLOSE_CM ||
        Robot::ir_star->read_cm() < OBSTACLE_AVOIDANCE_STRAFE_TOO_CLOSE_CM)
    {
        serlog("no room to strafe, moving to stop\n");

        Robot::motor_controller->stop();

        Robot::current_state = PathFinding::Stopped;
    }

    // transition to forward state once it can no longer detect
    // the obstacle in front.
    if (!ObstacleAvoidance::keep_avoiding())
    {
        serlog("finished strafing, moving to forward\n");

        // stop the motors and record how long it took
        Robot::motor_controller->stop();
        AVOIDANCE_LENGTH = millis() - AVOIDANCE_STARTED;

        Robot::motor_controller->forward();
        FORWARD_STARTED = millis();
        Robot::current_state = ObstacleAvoidance::Forward;
    }
}


void ObstacleAvoidance::Forward()
{
    if (ObstacleAvoidance::detect_wall())
    {
        serlog("detected wall during oa forward\n");

        Robot::current_state = PathFinding::Tumble;
    }

    if ((millis() - FORWARD_STARTED) > OBSTACLE_AVOIDANCE_MOVE_FORWARD_DURATION_MILLIS)
    {
        serlog("finished forward, moving to recovery\n");

        Robot::motor_controller->stop();

        // start the recovery manuveure.
        RECOVERY_FP();
        RECOVERY_STARTED = millis();

        Robot::current_state = ObstacleAvoidance::Recovery;
    }
}


void ObstacleAvoidance::Recovery()
{
    if ((millis() - RECOVERY_STARTED) >= AVOIDANCE_LENGTH)
    {
        serlog("finished recovery, going back to pathfinding\n");

        Robot::motor_controller->forward();

        Robot::current_state = Bob;
    }
}


bool ObstacleAvoidance::detect_wall()
{
    bool port = Robot::ir_port_bow->read_cm() < PATHFINDING_IR_PORT_BOW_WALL_DETECTION_THRESHOLD;
    bool star = Robot::ir_star_bow->read_cm() < PATHFINDING_IR_STAR_BOW_WALL_DETECTION_THRESHOLD;
    bool sonr = false;

    float sonar_cm = 0;

    if (
        Robot::sonar->read_cm_checked(&sonar_cm) ||
        Robot::sonar->read_cm_checked(&sonar_cm) ||
        Robot::sonar->read_cm_checked(&sonar_cm));

    sonr = sonar_cm < PATHFINDING_SONAR_WALL_DETECTION_THRESHOLD;

    if (port && star && sonr) return true;
    return false;
}


bool ObstacleAvoidance::keep_avoiding()
{
    float ir_cm = RECOVERY_SENSOR();
    float sonar_cm = 0;

    if (Robot::sonar->read_cm_checked(&sonar_cm) ||
        Robot::sonar->read_cm_checked(&sonar_cm) ||
        Robot::sonar->read_cm_checked(&sonar_cm) );

    bool sonr = sonar_cm < PATHFINDING_SONAR_OBSTACLE_AVOIDANCE_THRESHOLD;
    bool ir = ir_cm < PATHFINDING_IR_OBSTACLE_AVOIDANCE_THRESHOLD;

    return ir || sonr;
}


bool ObstacleAvoidance::detect_obstacle()
{
    bool port = Robot::ir_port_bow->read_cm() < PATHFINDING_IR_PORT_BOW_OBSTACLE_DETECTION_THRESHOLD;
    bool star = Robot::ir_star_bow->read_cm() < PATHFINDING_IR_STAR_BOW_OBSTACLE_DETECTION_THRESHOLD;
    bool sonr = false;

    float sonar_cm = 0;

    if (
        Robot::sonar->read_cm_checked(&sonar_cm) ||
        Robot::sonar->read_cm_checked(&sonar_cm) ||
        Robot::sonar->read_cm_checked(&sonar_cm));

    sonr = sonar_cm < PATHFINDING_SONAR_OBSTACLE_DETECTION_THRESHOLD;

    if (port || star || sonr) return true;
    return false;
}
