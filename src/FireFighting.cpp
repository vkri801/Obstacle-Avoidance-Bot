/*! \file
    \brief Implementation of the FireFighting state machine functions.
    \see FireFighting
    \see \ref state_machines
    \see Robot
*/

#include "FireFighting.h"
#include "PathFinding.h"
#include "Robot.h"

#include "ObstacleAvoidance.h"

#include "utils.h"

void FireFighting::Start()
{
    serlog("beginning fire tracking\n");

    Robot::current_state = FireFighting::TrackFire;
}


void FireFighting::TrackFire()
{
    // nb: `track_fire()` returns true once the fan is facing the fire.
    if (Robot::firehose->track_fire())
    {
        serlog("done tracking, fighting fire\n");

        Robot::firehose->on();

        Robot::current_state = FireFighting::FightFire;
    }
}


void FireFighting::FightFire()
{
    if (!Robot::firehose->fire_detected())
    {
        serlog("fire put out, moving back to oa\n");

        Robot::firehose->off();
        Robot::firehose->reset_servo_pos();

        ObstacleAvoidance::set_bob(PathFinding::Normal);
        Robot::current_state = ObstacleAvoidance::Start;
    }
}
