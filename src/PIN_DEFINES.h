/*! \file
    \brief Definition of pins that are used by the robot.
*/

#ifndef PIN_DEFINES_H
#define PIN_DEFINES_H

/// Sonar trigger pin.
/**
\see Sonar
*/
#define SONAR_TRIG_PIN 48

/// Sonar echo pin
/**
\see Sonar
*/
#define SONAR_ECHO_PIN 49


/// The IR sensors
/**
\see IRSensor
*/
#define IR_PORT_BOW_PIN A4
#define IR_STAR_BOW_PIN A6
#define IR_PORT_PIN A5
#define IR_STAR_PIN A7


/// The main drive motors, front/rear left/right
/**
\see MotorController
*/
#define FL_MOTOR_PIN 46
#define FR_MOTOR_PIN 51
#define RL_MOTOR_PIN 47
#define RR_MOTOR_PIN 50


/// The firehose pins
/**
\see Firehose
*/
#define PORT_PT_PIN A3
#define STAR_PT_PIN A2
#define FIREHOSE_FAN_PIN 30
#define FIREHOSE_SERVO_PIN 9

#endif
