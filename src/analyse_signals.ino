/*! \file analyse_signals.ino
    \brief A program for analysing the signals from the MPU.

This file contains a program which simply reads values off the MPU and dumps
the results over serial, in JSON format.

# Usage:

Simply build and upload the program using the Arduino IDE. The program will
continuously dump values over serial.

In order to collect the results, you will have to open the serial monitor in
the Arduino IDE, copy the data into your favourite text editor, and add `[` and
`]` to the beginning and end of the file, respectively.

Due to the nature of the data collection, you might only have part of an object
at the beginning or end of the file. You'll need to delete these in order for
the file to be valid JSON.
*/

#ifdef ANALYSE_SIGNALS
#warning Compiling signal program

#include "MPU.h"
#include "Integrator.h"
#include "utils.h"

#define ACCL_FILT 1
#define GYRO_FILT 1

HardwareSerial* SerialCom;
MPU* mpu;
float start_time;

void setup()
{
    SerialCom = &Serial; // Cable
    // SerialCom = &Serial1; // Bluetooth

    SerialCom->begin(115200);
    mpu = new MPU(ACCL_FILT, GYRO_FILT);
    start_time = Utils::seconds();
}

void loop()
{
    // See utils for definition of the code for sending data in JSON format.

    jstart;

    mpu->update();

    float ax, ay, az;
    float vx, vy, vz;
    float px, py, pz;
    float gx, gy, gz;

    mpu->acc(&ax, &ay, &az);
    mpu->vel(&vx, &vy, &vz);
    mpu->pos(&px, &py, &pz);
    mpu->ang(&gx, &gy, &gz);

    jfloat(ax); jnext;
    jfloat(ay); jnext;
    jfloat(az); jnext;

    jfloat(vx); jnext;
    jfloat(vy); jnext;
    jfloat(vz); jnext;

    jfloat(px); jnext;
    jfloat(py); jnext;
    jfloat(pz); jnext;

    jfloat(gx); jnext;
    jfloat(gy); jnext;
    jfloat(gz); jnext;

    jkey("t"); jval(seconds() - start_time, 6);
    jend; jnext;
}

#endif
