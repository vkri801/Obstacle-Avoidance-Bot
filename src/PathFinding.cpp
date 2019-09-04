/*! \file
    \brief Implementation of the PathFinding state machine functions.
    \see PathFinding
    \see \ref state_machines
    \see Robot
*/

#include "PathFinding.h"
#include "Robot.h"

#include "PARAMETERS.h"

#include <Arduino.h>

#include "ObstacleAvoidance.h"

#include "utils.h"

void PathFinding::Start()
{
    Robot::motor_controller->forward();
    Robot::current_state = PathFinding::Normal;

    serlog("moving to path normal\n");
}

/// When the tumble was started.
long TUMBLE_STARTED;

/// When the turn was started.
long TURN_STARTED;

void PathFinding::Normal()
{
    if (ObstacleAvoidance::detect_wall())
    {
        serlog("detected a wall, moving to tumble\n");

        // stop and do a tumble-turn
        Robot::motor_controller->cw();
        TUMBLE_STARTED = millis();

        Robot::current_state = PathFinding::Tumble;
    }

    else if (ObstacleAvoidance::detect_obstacle())
    {
        serlog("detected an obstacle, moving to oa\n");

        // stop and let OA take over.
        Robot::motor_controller->stop();

        ObstacleAvoidance::set_bob(PathFinding::Normal);
        Robot::current_state = ObstacleAvoidance::Start;
    }

    else if (abs(Robot::mpu->heading()) > PATHFINDING_HEADING_DRIFT_LIMIT)
    {
        Robot::motor_controller->stop();
        Robot::current_state = PathFinding::CorrectHeading;

        if (Robot::mpu->heading() > 0.0)
        {
            Robot::motor_controller->cw();
        }

        else
        {
            Robot::motor_controller->ccw();
        }
    }
}

void PathFinding::CorrectHeading()
{
    if (abs(Robot::mpu->heading()) < PATHFINDING_HEADING_DRIFT_LIMIT)
    {
        Robot::motor_controller->forward();
        Robot::current_state = PathFinding::Normal;
    }
}

typedef void (*TurnDirection)(void);

extern void strafe_right();

extern void strafe_left();

TurnDirection TURN_DIRECTION;

void swap_turn_dir()
{
    if (TURN_DIRECTION == strafe_right) TURN_DIRECTION = strafe_left;
    else TURN_DIRECTION = strafe_right;
}


void PathFinding::Tumble()
{
    if ((millis() - TUMBLE_STARTED) >= PATHFINDING_TUMBLE_DURATION_MILLIS)
    {
        serlog("tumble finished, moving to turn\n");

        swap_turn_dir();
        TURN_DIRECTION();
        TURN_STARTED = millis();

        Robot::current_state = PathFinding::Turn;
    }
}


void PathFinding::Turn()
{
    if ((millis() - TURN_STARTED) >= PATHFINDING_TURN_DURATION_MILLIS)
    {
        serlog("turn finished, moving back to normal\n");

        Robot::motor_controller->forward();

        Robot::current_state = PathFinding::Normal;
    }
}


void PathFinding::Stopped() {}
