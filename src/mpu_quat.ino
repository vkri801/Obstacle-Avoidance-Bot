/*! \file
    \brief Testing program for using Quaterions with the MPU
    \author Vincent Krishna

*/

#ifdef MPU_QUAT

#include "quaternionFilters.h"


#include <Arduino.h>
#include <avr/sleep.h>

#include "Sonar.h"
#include "MotorController.h"
#include "IRSensor.h"
#include "Firehose.h"

#include "MPU.h"

#include "PathFinding.h"
#include "ObstacleAvoidance.h"
#include "FireFighting.h"
#include "Starting.h"

#include "Battery.h"

#include "PIN_DEFINES.h"
#include "PARAMETERS.h"

int TABLEVEL;

namespace Robot
{
    /// The sonar module.
    /**
    \see Sonar
    */
    Sonar* sonar;
    MPU* mpu;
    /// For controlling the motors.
    /**
    \see MotorController
    */
    MotorController* motor_controller;

    IRSensor* ir_port_bow; ///< The IR sensor on the port bow.       
    IRSensor* ir_star_bow; ///< The IR sensor on the starboard bow.  
    IRSensor* ir_port;     ///< The IR sensor on the port side.      
    IRSensor* ir_star;     ///< The IR sensor on the starboard side. 

    /// The fan, phototransistors and servo.
    /**
    \see Firehose
    */
    Firehose* firehose;

    void (*current_state)(void);
}

#include "test.h"

using namespace Robot;

/// Pointer to the serial device to use.
/**
*/
HardwareSerial* SerialCom;

/// Arduino setup function
/**
This initialises everything (sensors, state machine etc).
*/
void setup()
{

    mpu = new MPU();
    SerialCom = &Serial;
    SerialCom->begin(115200);
    SerialCom->println("serial link initialised");
    SerialCom->println("beginning setup");

    // setup sensors and actuators
    sonar = new Sonar();
    motor_controller = new MotorController();
    motor_controller->set_speed(MOTOR_DEFAULT_SPEED);

    ir_port_bow = new IRSensor(IR_PORT_BOW_PIN);
    ir_star_bow = new IRSensor(IR_STAR_BOW_PIN);
    ir_port     = new IRSensor(IR_PORT_PIN);
    ir_star     = new IRSensor(IR_STAR_PIN);

    firehose = new Firehose();


    // setup state machine
    current_state = ROBOT_STARTING_STATE;

    SerialCom->println("setup complete");
}
void shutdown()
{
    delete sonar;
    delete motor_controller;
    delete ir_port_bow;
    delete ir_star_bow;
    delete ir_port;
    delete ir_star;
    delete firehose;
    delete mpu;

    SerialCom->println("device is shutting down");

    sleep_enable();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_cpu();

    // the CPU should never wake from this, but just in case...
    //
    // NOTE: otherwise, could cause anything to happen since the
    // pointers have been free'd.
    while (1);
}


#define state_case(item) if (item == Robot::current_state) return #item

const char* current_state_name()
{
    state_case(Starting::Start);
    state_case(Starting::DriveForward1);
    state_case(PathFinding::Start);
    state_case(PathFinding::Normal);
    state_case(PathFinding::Tumble);
    state_case(PathFinding::Turn);
    state_case(PathFinding::Stopped);
    state_case(ObstacleAvoidance::Start);
    state_case(ObstacleAvoidance::Strafing);
    state_case(ObstacleAvoidance::Forward);
    state_case(ObstacleAvoidance::Recovery);
    state_case(FireFighting::Start);
    state_case(FireFighting::TrackFire);
    state_case(FireFighting::FightFire);
    state_case(Starting::Start);
    state_case(Starting::AlignmentCoarseMag);
    state_case(Starting::DriveForward1);
    state_case(Starting::AlignmentFineIR);
    state_case(Starting::RotateLeft1);
    state_case(Starting::DriveForward2);
    state_case(Starting::RotateLeft2);
    state_case(Testing::Start);

    return "Unknown state";
}

// Conditional logging.
#ifdef LOG
#define serlog(...) SerialCom->print(__VA_ARGS__)
#else
#define serlog(...)
#endif

/// The main program loop.
/**
For now, there are only two tasks; checking if the battery is ok, and the
main stuff.

Moves to shutdown if the robot is low on battery.
*/
void loop()
{
    if (Battery::ok())
    {
        mpu->update();
        current_state();
    }

    else shutdown();

    delay(MAIN_LOOP_DELAY);
}


#endif
