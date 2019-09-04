/*! \file PARAMETERS.h
    \brief Parameters for the robot.

\note TUNING AS OF SUNDAY 27TH OF MAY
\note SELF-REPORTED BATTERY VOLTAGE: 8.29 VOLTS (TOTAL).

This file contains definitions for the various parameters for the robot.

Basically, it's like the config file for the robot.
*/

#ifndef PARAMETERS_H
#define PARAMETERS_H

////// GENERAL //////

/// The starting state for the robot
/**
*/
#define ROBOT_STARTING_STATE Starting::Start;

/// The amount of delay between loop iterations
/**
\warning This should be at least 1, otherwise shit won't work.
*/
#define MAIN_LOOP_DELAY 50

/// Logging control
/**
Comment this out to disable logging.
*/
#define LOG

/// How long it takes for a 180 degree turn (millis)
/**
*/
#define TURN_180 2000

/// How long it takes for a 90 degree turn (millis)
/**
*/
#define TURN_90 1000


////// STARTING STATE PARAMETERS //////


// the length of the rotations
#define STARTING_ROTATE_1_DURATION TURN_90
#define STARTING_ROTATE_2_DURATION TURN_90

/// The threshold for alignment with track north.
#define STARTING_MAG_ALIGNMENT_THRESHOLD 0.1

/// TODO: Record the magnetic field vector for track north.
#define STARTING_MAG_X 212.121
#define STARTING_MAG_Y 643.110
#define STARTING_MAG_Z 264.15

#define STARTING_MAG_MAG (              \
    (STARTING_MAG_X * STARTING_MAG_X) + \
    (STARTING_MAG_Y * STARTING_MAG_Y) + \
    (STARTING_MAG_Z * STARTING_MAG_Z) )


////// MOTOR CONTROLLER PARAMETERS //////


/// The maximum motor speed.
///
/// The servos are controlled using `writeMicroseconds(1500 + delta)`. This
/// value is the limit for `delta`.
///
/// This value should be set such that the motors still spin properly at max
/// speed.
#define MOTOR_MAX_SPEED_VAL 300


/// The default motor speed.
/**
\warning DO NOT CHANGE THIS FROM 200
*/
#define MOTOR_DEFAULT_SPEED 200


////// PATHFINDING PARAMETERS //////


/// Thresholds for detecting a wall
///
#define PATHFINDING_SONAR_WALL_DETECTION_THRESHOLD 10.0
#define PATHFINDING_IR_PORT_BOW_WALL_DETECTION_THRESHOLD 10.0
#define PATHFINDING_IR_STAR_BOW_WALL_DETECTION_THRESHOLD 10.0

/// Thresholds for detecting an obstacle
///
#define PATHFINDING_SONAR_OBSTACLE_DETECTION_THRESHOLD 8.0
#define PATHFINDING_IR_PORT_BOW_OBSTACLE_DETECTION_THRESHOLD 6.0
#define PATHFINDING_IR_STAR_BOW_OBSTACLE_DETECTION_THRESHOLD 6.0

/// Thresholds for avoiding an obstacle
#define PATHFINDING_SONAR_OBSTACLE_AVOIDANCE_THRESHOLD 10.0
#define PATHFINDING_IR_OBSTACLE_AVOIDANCE_THRESHOLD 15.0

/// How long to strafe for during the turn
///
#define PATHFINDING_TURN_DURATION_MILLIS 1100

/// How long to tumble for.
/**
*/
#define PATHFINDING_TUMBLE_DURATION_MILLIS TURN_180

#define PATHFINDING_HEADING_DRIFT_LIMIT 0.5

////// OBSTACLE AVOIDANCE PARAMETERS //////


/// When avoiding an obstacle, how long to move forward for.
#define OBSTACLE_AVOIDANCE_MOVE_FORWARD_DURATION_MILLIS 1000

/// If the readings from the IR sensors are less than this, then there is
/// not enough room to continue strafing.
#define OBSTACLE_AVOIDANCE_STRAFE_TOO_CLOSE_CM 5


////// FIREHOSE PARAMETERS //////


/// The amount of gain on the fire-tracking controller.
///
#define FIREHOSE_TRACKING_GAIN 0.2


/// If the difference between the phototransistor readings is below this
/// threshold, then the fan should be facing the fire.
#define FIREHOSE_FAN_FACING_FIRE_THRESHOLD 10


/// If *either* phototransistor has a reading above this value, then
/// we've found a fire.
#define FIREHOSE_FIRE_DETECTION_THRESHOLD 600



////// SONAR //////


/// The amount of filtering on the sonar.
#define SONAR_FILTER_PARAM 0.3


#endif
