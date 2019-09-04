/*! \file
    \brief Provides the ObstacleAvoidance state machine.
    \see ObstacleAvoidance
    \see FireFighting
    \see PathFinding
    \see \ref state_machines
*/

#ifndef OBSTACLE_AVOIDANCE_H
#define OBSTACLE_AVOIDANCE_H

/// The Obstacle Avoidance state machine.
/**
This state machine is responsible for avoiding obstacles.

This state first checks if the obstacle is on fire. If it is, it hands
over to the FireFighing state machine.

Next, it uses the port and starboard IR sensors to determine the path
with the most space, and moves either left or right accordingly.

The robot moves forward, past the obstacle.

Finally, the robot enters the "path recovery" state, where it strafes
back in line with the original path.

\see FireFighting
\see PathFinding
\see \ref state_machines
*/
namespace ObstacleAvoidance
{
    /// The Starting state.
    /**
    This first checks if the obstacle is on fire, and, 
    if it is, it hands control over to the FireFighting machine. It then
    decides whether to move left or right to avoid the obstacle.
    */
    void Start();

    /// The robot is strafing around the obstacle.
    /**
    \note If the IR sensors on the side detect that there is too little
    space to continue, then the robot will move into the PathFinding::Stopped
    state.

    \see PARAMETERS.h
    */
    void Strafing();

    /// The robot is moving forward, past the obstacle, checking for additional
    /// obstacles as it goes.
    void Forward();

    /// The robot is recovering it's original path before it encountered the
    /// obstacle.
    void Recovery();

    /// Returns true if an obstacle is in front of the robot.
    /**
    For now, this is just done by checking if any of:

    - The Sonar module,
    - The IR sensors on the bow

    Are returning readings of fewer than 10cm (configurable in PARAMETERS.h).

    \note Sonar calls can fail if the echo takes too long to come back. This
    function will try up to three times to read from the Sonar, and if it still
    fails, then the function will return false.

    \see PARAMETERS.h
    \see Sonar
    */
    bool detect_obstacle();

    /// Returns true if should keep avoiding
    /**
    */
    bool keep_avoiding();

    /// Returns true if there is a wall in front of the robot.
    /**
    */
    bool detect_wall();

    void set_bob(void (*bob)(void));
}

#endif

