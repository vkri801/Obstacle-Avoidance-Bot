/*! \file
    \brief Provides the PID class.
    \see PID
*/

#ifndef PID_H
#define PID_H

#include "Differentiator.h"
#include "Integrator.h"

/// Performs PID control of a variable.
/**
Use the `update()` method to specify the values of the process variable.

`update()` will return a value that should be passed on to your plant.
*/
class PID
{
    // For differentiating and integrating error, respectively.
    Differentiator dedt;
    Integrator edt;

    public:

    /// Initialises a PID controller with the corresponding gains.
    /**
    Obviously, the gains should be non-negative.
    */
    PID(float kp, float ki, float kd);

    float kp; ///< Proportional gain of this controller.
    float ki; ///< Integral gain of this controller.
    float kd; ///< Derivative gain of this controller.

    float reference; ///< The current reference or setpoint.

    /// Performs one step of PID control.
    /**
    \param pv The current value of your process variable that you are trying
    to control.

    \return `float` The control effort, which should be passed back to your
    plant.
    */
    float update(float pv);
};

#endif
