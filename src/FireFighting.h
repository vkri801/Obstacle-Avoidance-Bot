/*! \file
    \brief Declaration of the FireFighting state machine.
    \see FireFighting
    \see ObstacleAvoidance
    \see PathFinding
    \see \ref state_machines
*/

#ifndef FIRE_FIGHTING_H
#define FIRE_FIGHTING_H

/// The FireFighing state machine.
/**
The FireFighting state machine is responsible for, of course, delivering cookies.

Wait, that's not right; fighting fires, that's what it's for.

It consists of three states:

* `FireFighting::Start` This is the starting state. The machine will move
  to the TrackFire state.

* `FireFighting::TrackFire` When the robot is in this state, it actuating the
  servo to make the fan face the fire. It does this via the Firehose.  Once the
  Firehose has completed tracking the fire and the fan is pointed at the fire,
  the state machine moves into the FightFire state.

* `FireFighting::FightFire` The robot leaves the fan on until the lamp goes *
  out. Once it can no longer detect a fire, the robot moves back to the
  ObstacleAvoidance state.

\see ObstacleAvoidance
\see PathFinding
*/
namespace FireFighting
{
    /// The start state
    ///
    void Start();

    /// The fire-tracking state.
    /**
    This makes the fan turn towards the fire.

    Once the fan is facing the fire, the state machine moves into the FightFire
    state.
    */
    void TrackFire();

    /// The fire-fighting state.
    /**
    In this state, the robot leaves the fan on until the fire has been
    put out.

    Once the fire has been put out, the robot moves back to the ObstacleAvoidance
    state.
    */
    void FightFire();
}

#endif
