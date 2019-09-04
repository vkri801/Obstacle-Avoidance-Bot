/*! \file
    \brief Implementation of the MotorController class
    \see MotorController
*/

#include "MotorController.h"

#include <Arduino.h>

#include "PIN_DEFINES.h"
#include "PARAMETERS.h"

#include "utils.h"

MotorController::MotorController()
{
    serlog("init motor controller\n");

    pinMode(FL_MOTOR_PIN, OUTPUT);
    pinMode(FR_MOTOR_PIN, OUTPUT);
    pinMode(RL_MOTOR_PIN, OUTPUT);
    pinMode(RR_MOTOR_PIN, OUTPUT);

    fl.attach(FL_MOTOR_PIN);
    fr.attach(FR_MOTOR_PIN);
    rl.attach(RL_MOTOR_PIN);
    rr.attach(RR_MOTOR_PIN);
}


MotorController::~MotorController()
{
    fl.detach();
    fr.detach();
    rl.detach();
    rr.detach();

    pinMode(FL_MOTOR_PIN, INPUT);
    pinMode(FR_MOTOR_PIN, INPUT);
    pinMode(RL_MOTOR_PIN, INPUT);
    pinMode(RR_MOTOR_PIN, INPUT);
}


/// Correction values for the motors.
///
/// Making these values larger makes the motor in question turn slower.
///
/// These are set on a per-direction basis, see the direction functions
/// below.
int FL_MOTOR_CORRECTION = 0;
int FR_MOTOR_CORRECTION = 0;
int RL_MOTOR_CORRECTION = 0;
int RR_MOTOR_CORRECTION = 0;


void MotorController::set_speed(int speed_val)
{
    if (speed_val >  MOTOR_MAX_SPEED_VAL) speed_val =  MOTOR_MAX_SPEED_VAL;
    if (speed_val < -MOTOR_MAX_SPEED_VAL) speed_val = -MOTOR_MAX_SPEED_VAL;
    this->speed_val = speed_val;
}


void MotorController::write_speed(int fl, int fr, int rl, int rr)
{
    // the motors on the starboard side are wired up the same as those on
    // the port side, but the motors on the starboard side face the opposite
    // way, so in order for things to work, you have to negate the starboard
    // control values.
    fr = -fr;
    rr = -rr;

    this->fl.writeMicroseconds(1500 + fl * (this->speed_val - FL_MOTOR_CORRECTION));
    this->fr.writeMicroseconds(1500 + fr * (this->speed_val - FR_MOTOR_CORRECTION));
    this->rl.writeMicroseconds(1500 + rl * (this->speed_val - RL_MOTOR_CORRECTION));
    this->rr.writeMicroseconds(1500 + rr * (this->speed_val - RR_MOTOR_CORRECTION));

    // reset the correction factors
    // (not all of the directions need correcting on all motors)
    FL_MOTOR_CORRECTION = 0;
    FR_MOTOR_CORRECTION = 0;
    RL_MOTOR_CORRECTION = 0;
    RR_MOTOR_CORRECTION = 0;
}


// see below for use
#define FORWARDS   1
#define BACKWARDS -1
#define STOPPED    0

// note that for each of these functions, the layout in the code is the same
// as the layout on the robot.


void MotorController::stop()
{
    this->write_speed(
        STOPPED, STOPPED,
        STOPPED, STOPPED
    );
}


void MotorController::forward()
{
    // pulls a little to the right, so we slow down the left motors slightly.
    FL_MOTOR_CORRECTION = 19;
    RL_MOTOR_CORRECTION = 19;

    this->write_speed(
        FORWARDS, FORWARDS,
        FORWARDS, FORWARDS
    );
}


void MotorController::reverse()
{
    this->write_speed(
        BACKWARDS, BACKWARDS,
        BACKWARDS, BACKWARDS
    );
}


void MotorController::ccw()
{
    this->write_speed(
        BACKWARDS, FORWARDS,
        BACKWARDS, FORWARDS
    );
}


void MotorController::cw()
{
    this->write_speed(
        FORWARDS, BACKWARDS,
        FORWARDS, BACKWARDS
    );
}


void MotorController::strafe_right()
{
    FL_MOTOR_CORRECTION = 10;
    FR_MOTOR_CORRECTION = 10;

    this->write_speed(
        FORWARDS , BACKWARDS,
        BACKWARDS, FORWARDS 
    );
}


void MotorController::strafe_left()
{
    this->write_speed(
        BACKWARDS, FORWARDS ,
        FORWARDS , BACKWARDS
    );
}

