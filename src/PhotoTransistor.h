/*! \file
    \brief Provides the PhotoTransistor class.
    \see PhotoTransistor
*/

#ifndef PHOTOTRANSISTOR_H
#define PHOTOTRANSISTOR_H

/// Represents a phototransistor mounted on the fan.
/**
The Firehose uses the phototransistors mounted to the fan to detect the
location of the fire, and turn the fan towards it.

\see Firehose
*/
class PhotoTransistor
{
    int pin;

    public:

    /// Initialises the PhotoTransistor.
    /**
    This is just setting the pinMode.
    */
    PhotoTransistor(int pin);

    /// Performs a raw `analogRead()` of the pin.
    ///
    int read_raw();
};

#endif
