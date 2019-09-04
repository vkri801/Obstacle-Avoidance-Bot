/*! \file
    \brief Implementation of the Starting state machine functions.
    \see Starting
    \see \ref state_machines
    \see Robot
*/

#include "math.h"

#include "Starting.h"

#include "ObstacleAvoidance.h"
#include "PathFinding.h"

#include "Robot.h"

#include "PARAMETERS.h"

#include "json.h"

float magval;
void Starting::Start()
{
    Robot::motor_controller->stop();

    Robot::current_state = Starting::AlignmentCoarseMag;

    // for now; just rotate the same way; later we can choose which one.
    Robot::motor_controller->ccw();
}

bool aligned_to_track()
{ 
     magval = Robot::mpu->mag();
    Serial.print(magval);
    if(magval > -105.00 & magval < -95.00){
      return true;
    }

    else return false;
}


void Starting::AlignmentCoarseMag()
{
    if (aligned_to_track())
    {
        magval = Robot::mpu->mag();
        Serial.print(magval);
        Robot::motor_controller->forward();
        Robot::current_state = Starting::DriveForward1;
    }
}


void Starting::DriveForward1()
{
    if (ObstacleAvoidance::detect_wall())
    {
        Robot::motor_controller->stop();
        Robot::current_state = Starting::AlignmentFineIR;
    }

    else if (ObstacleAvoidance::detect_obstacle())
    {
        Robot::motor_controller->stop();

        ObstacleAvoidance::set_bob(Starting::DriveForward1);
        Robot::current_state = ObstacleAvoidance::Start;
    }
}


int ROTATE_1_STARTED;


void Starting::AlignmentFineIR()
{
    int port;
    int star;

    do
    {
        port = Robot::ir_port_bow->read_raw();
        star = Robot::ir_star_bow->read_raw();

        if (port > star) Robot::motor_controller->ccw();
        if (star > port) Robot::motor_controller->cw();
    }
    while (port != star);

    Robot::motor_controller->ccw();
    ROTATE_1_STARTED = millis();
    Robot::current_state = Starting::RotateLeft1;
}


void Starting::RotateLeft1()
{
    if ((millis() - ROTATE_1_STARTED) > STARTING_ROTATE_1_DURATION)
    {
        Robot::motor_controller->forward();
        Robot::current_state = Starting::DriveForward2;
    }
}


int ROTATE_2_STARTED;


void Starting::DriveForward2()
{
    if (ObstacleAvoidance::detect_wall())
    {
        Robot::motor_controller->ccw();
        ROTATE_2_STARTED = millis();
        Robot::current_state = Starting::RotateLeft2;
    }

    else if (ObstacleAvoidance::detect_obstacle())
    {
        Robot::motor_controller->stop();
        ObstacleAvoidance::set_bob(Starting::DriveForward2);
    }
}


void Starting::RotateLeft2()
{
    if ((millis() - ROTATE_2_STARTED) > STARTING_ROTATE_2_DURATION)
    {
        Robot::mpu->reset_heading();

        Robot::motor_controller->forward();
        Robot::current_state = PathFinding::Start;
    }
}

