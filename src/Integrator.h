/*! \file
    \brief Provides the Integrator class.
    \see Integrator
    \see Differentiator
*/

#ifndef INTEGRATOR_H
#define INTEGRATOR_H

/// Integrates a function using the trapezium rule.
/**
Integrates a function in real-time. Pass it successive values of the 
function that you want to integrate, and it will return estimates of the
integral w.r.t time.

This is a real-time function; it uses `micros()` internally for the time delta
between values.

\see Differentiator
*/
class Integrator
{
    float t1;
    float f1;

    float val;

    public:

    Integrator();

    /// Returns the next value of the integral, given the current value of the function.
    /**
    */
    float update(float f0);

    /// Returns the last value of the integral.
    ///
    float value();

    /// Resets the value of the integral.
    ///
    void reset();
};

#endif
