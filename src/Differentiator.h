/*! \file
    \brief Provides the Differentiator class.

Provides the Differentiator class, which computes the derivative of a function.

\see Differentiator
\see Integrator
*/

#ifndef DIFFERENTIATOR_H
#define DIFFERENTIATOR_H

/// Differentiates a function using the backward difference method.
/**
Differentiates a function in real-time. Pass it successive values of the
function that you want to differentiate, and it will return estimates of the
derivative w.r.t time.

This is real-time function; it uses `micros()` internally for the time delta
between values.

# Usage:

Something like this:

    float acceleration = Differentiator();
    while(1)
    {
        float current_speed = read_speed();
        float current_accel = acceleration.update(current_speed);
    }

i.e you use the `update` method to successively pass values of the function 
you want to differentiate.

You need one instance of this class for each function you want to differentiate.

\see Integrator
*/
class Differentiator
{
    float t1;
    float f1;

    float val;

    public:

    Differentiator();

    /// Returns the next value of the derivative, given the next value of the function.
    /**
    \param f0 The current value of the function.
    \return `float`; The current value of the derivative.
    */
    float update(float f0);

    /// Returns the current value of the derivative.
    ///
    float value();
};

#endif
