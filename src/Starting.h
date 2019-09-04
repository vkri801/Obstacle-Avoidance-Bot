/*! \file
    \brief Provides the Starting state machine.
    \see PathFinding
    \see ObstacleAvoidance
    \see FireFighting
    \see \ref state_machines
*/

#ifndef STARTING_H
#define STARTING_H

/// The Starting state machine
/**
This state machine performs the inital alignment of the robot.

* We first perform a coarse alignment using the compass.
* Then, drive forward until we hit a wall.
* Perform fine alignment using the front IR.
* Rotate 90 degrees left.
* Drive forward until we hit a corner.
* Rotate 90 degrees left.
* Move into normal PathFinding state.

*/
namespace Starting
{
    /// The starting state.
    /**
    Begins the alignment with the compass.
    */
    void Start();

    /// Performs coarse alignment using the magnetometer.
    /**
    */
    void AlignmentCoarseMag();

    /// Drives forward until the wall is detected.
    /**
    */
    void DriveForward1();

    /// Performs fine alignment with the wall using the front IR.
    /**
    */
    void AlignmentFineIR();

    /// Rotates to be parallel with the short wall.
    /**
    */
    void RotateLeft1();

    /// Drives forward to the corner.
    /**
    */
    void DriveForward2();

    /// Rotates to start the run.
    /**
    */
    void RotateLeft2();
}

#endif
