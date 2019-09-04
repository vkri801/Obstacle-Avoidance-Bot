/*! \file
    \brief Provides the PathFinding state machine.
    \see PathFinding
    \see ObstacleAvoidance
    \see FireFighting
    \see \ref state_machines
*/

#ifndef PATHFINDING_H
#define PATHFINDING_H

/// The PathFinding state machine.
/**
This state machine is responsible for pathfinding.

During normal operation, the robot simply moves forward. If an obstacle 
is detected, the state machine hands over to the Obstacle Avoidance
state machine.

If a wall is detected, the machine performs a tumble turn. You know, like in
swimming. This consists of a "tumble", where the robot rotates 180 degrees, and
a "turn", where the robot strafes to the next row to explore.

\see ObstacleAvoidance
\see FireFighting
\see \ref state_machines
*/
namespace PathFinding
{
    /// The starting state. 
    /**
    This just set the motors to move the robot forward, and then moves into
    the Normal state.
    */
    void Start();

    /// The normal state for the pathfinding machine.
    /**
    In the normal state, the robot simply moves forwards.

    If the machine detects a wall, it will perform a tumble-turn, like in
    swimming. This involves a 180 degree spin on axis, followed by a strafe to
    the right.

    If this machine detects an obstacle, it hands control to the Obstacle
    Avoidance machine, which will also fight the fire if there is one.

    \see ObstacleAvoidance
    \see FireFighting
    \see PARAMETERS.h
    */
    void Normal();

    /// If the heading drifts too far, then we correct.
    /**
    */
    void CorrectHeading();

    /// Performs the tumble.
    /**
    \see PathFinding
    */
    void Tumble();

    /// Performs the turn.
    /**
    \see PathFinding
    */
    void Turn();

    /// Stopped.
    /**
    \remark The robot can never move out of this state.
    */
    void Stopped();
}

#endif
