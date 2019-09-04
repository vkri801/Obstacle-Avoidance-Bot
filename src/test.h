/*! \file
    \brief testing stuff

*/

namespace Testing
{
    void Start()
    {
        Robot::motor_controller->set_speed(150);
        Robot::motor_controller->strafe_left();
    }
}
