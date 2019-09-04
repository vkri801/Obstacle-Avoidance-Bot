/** \file
    \brief Provides a basic filtering class, Filter.

This file provides the declaration of the Filter class, which is a class
that performs exponential smoothing.

\see Filter
*/

#ifndef FILTER_H
#define FILTER_H

/// Class which performs exponential smoothing.
/**
This class performs exponential smoothing, of the type:

    y1 = a*x0 + (1-a)*y0

*/
class Filter
{
    // The exponential smoothing factor.
    // Higher values -> *less* smoothing.
    // This should be between 0 and 1
    float alpha;
    float s1;

    public:

    /// Initialises a filter with the specified amount of filtering.
    /**
    \param alpha : The amount of smoothing. This should be a value between
    0 and 1. Higher values -> *less* smoothing.
    */
    Filter(float alpha);

    // Pass in the next value in the series that you are smoothing.
    // Returns the new value of the filter output.
    /// Returns the next value of the filtered series.
    /**
    \param s0 The current value of the function that you are smoothing.
    \return `float` The value of the function after applying exponential smoothing.
    */
    float update(float s0);

    /// Returns the current value of the filter output.
    ///
    float value();
};

#endif
