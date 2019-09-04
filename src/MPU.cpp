/*! \file
  \brief Implementatation of the MPU class.
  \see MPU
  */

#include "MPU9250.h"
#include "quaternionFilters.h"
#include <Arduino.h>

#include "MPU.h"
#include "Filter.h"
#include "utils.h"

#include "utils.h"

#define AHRS true         // Set to false for basic data read
int corrx,corry = 0;

int flag = 1;
float ori;

/// IMU object from the SparkFun library.
/**
*/
MPU9250 myIMU;

MPU::MPU()
{
    Wire.begin();

    // Read the WHO_AM_I register, this is a good test of communication
    byte c = myIMU.readByte(MPU9250_ADDRESS, WHO_AM_I_MPU9250);

    if (c == 0x71) // WHO_AM_I should always be 0x68
    {
        Serial.println("MPU9250 is online...");
        // Start by performing self test and reporting values
        myIMU.MPU9250SelfTest(myIMU.selfTest);

        // Calibrate gyro and accelerometers, load biases in bias registers
        myIMU.calibrateMPU9250(myIMU.gyroBias, myIMU.accelBias);

        myIMU.initMPU9250();

        // Read the WHO_AM_I register of the magnetometer, this is a good test of
        // communication
        byte d = myIMU.readByte(AK8963_ADDRESS, WHO_AM_I_AK8963);

        // Get magnetometer calibration from AK8963 ROM
        myIMU.initAK8963(myIMU.factoryMagCalibration);
    }

    else
    {
        Serial.print("Could not connect to MPU9250: 0x");
        Serial.println(c, HEX);
        while(1) ; // Loop forever if communication doesn't happen
    }

    this->update();
    this->heading_offset = this->heading();
}

void MPU::update()
{
    if (myIMU.readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01)
    {  
        myIMU.readAccelData(myIMU.accelCount);  // Read the x/y/z adc values
        myIMU.getAres();

        // Now we'll calculate the accleration value into actual g's
        // This depends on scale being set
        myIMU.ax = (float)myIMU.accelCount[0]*myIMU.aRes; // - accelBias[0];
        myIMU.ay = (float)myIMU.accelCount[1]*myIMU.aRes; // - accelBias[1];
        myIMU.az = (float)myIMU.accelCount[2]*myIMU.aRes; // - accelBias[2];

        myIMU.readGyroData(myIMU.gyroCount);  // Read the x/y/z adc values
        myIMU.getGres();

        // Calculate the gyro value into actual degrees per second
        // This depends on scale being set
        myIMU.gx = (float)myIMU.gyroCount[0]*myIMU.gRes;
        myIMU.gy = (float)myIMU.gyroCount[1]*myIMU.gRes;
        myIMU.gz = (float)myIMU.gyroCount[2]*myIMU.gRes;

        myIMU.readMagData(myIMU.magCount);  // Read the x/y/z adc values
        myIMU.getMres();
        // User environmental x-axis correction in milliGauss, should be
        // automatically calculated
        myIMU.magBias[0] = +470.;
        // User environmental x-axis correction in milliGauss TODO axis??
        myIMU.magBias[1] = +120.;
        // User environmental x-axis correction in milliGauss
        myIMU.magBias[2] = +125.;

        // Calculate the magnetometer values in milliGauss
        // Include factory calibration per data sheet and user environmental
        // corrections
        // Get actual magnetometer value, this depends on scale being set
        myIMU.mx = (float)myIMU.magCount[0]*myIMU.mRes*myIMU.factoryMagCalibration[0] -
            myIMU.magBias[0];
        myIMU.my = (float)myIMU.magCount[1]*myIMU.mRes*myIMU.factoryMagCalibration[1] -
            myIMU.magBias[1];
        myIMU.mz = (float)myIMU.magCount[2]*myIMU.mRes*myIMU.factoryMagCalibration[2] -
            myIMU.magBias[2];
    }

    // Must be called before updating quaternions!
    myIMU.updateTime();

    // Sensors x (y)-axis of the accelerometer is aligned with the y (x)-axis of
    // the magnetometer; the magnetometer z-axis (+ down) is opposite to z-axis
    // (+ up) of accelerometer and gyro! We have to make some allowance for this
    // orientationmismatch in feeding the output to the quaternion filter. For the
    // MPU-9250, we have chosen a magnetic rotation that keeps the sensor forward
    // along the x-axis just like in the LSM9DS0 sensor. This rotation can be
    // modified to allow any convenient orientation convention. This is ok by
    // aircraft orientation standards! Pass gyro rate as rad/s
    //  MadgwickQuaternionUpdate(ax, ay, az, gx*PI/180.0f, gy*PI/180.0f, gz*PI/180.0f,  my,  mx, mz);
    MadgwickQuaternionUpdate(
        myIMU.ax           , myIMU.ay           , myIMU.az,
        myIMU.gx*DEG_TO_RAD, myIMU.gy*DEG_TO_RAD, myIMU.gz*DEG_TO_RAD,
        myIMU.my           , myIMU.mx           , myIMU.mz,
        myIMU.deltat
    );

    ori = atan2((int)myIMU.mx,(int)myIMU.my)*RAD_TO_DEG;

    // Serial print and/or display at 0.5 s rate independent of data rates
    myIMU.delt_t = millis() - myIMU.count;

    myIMU.yaw   = atan2(2.0f * (*(getQ()+1) * *(getQ()+2) + *getQ() *
                *(getQ()+3)), *getQ() * *getQ() + *(getQ()+1) * *(getQ()+1)
            - *(getQ()+2) * *(getQ()+2) - *(getQ()+3) * *(getQ()+3));

    myIMU.pitch = -asin(2.0f * (*(getQ()+1) * *(getQ()+3) - *getQ() *
                *(getQ()+2)));

    myIMU.roll  = atan2(2.0f * (*getQ() * *(getQ()+1) + *(getQ()+2) *
                *(getQ()+3)), *getQ() * *getQ() - *(getQ()+1) * *(getQ()+1)
            - *(getQ()+2) * *(getQ()+2) + *(getQ()+3) * *(getQ()+3));

    myIMU.pitch *= RAD_TO_DEG;
    myIMU.yaw   *= RAD_TO_DEG;

    // Declination of SparkFun Electronics (40°05'26.6"N 105°11'05.9"W) is
    //    8° 30' E  ± 0° 21' (or 8.5°) on 2016-07-19
    // - http://www.ngdc.noaa.gov/geomag-web/#declination
    myIMU.yaw   -= 19.76;
    myIMU.roll  *= RAD_TO_DEG;

    myIMU.count = millis();
    myIMU.sumCount = 0;
    myIMU.sum = 0;
}

void MPU::accel(float* ax, float* ay, float* az)
{
    if (ax) *ax = myIMU.ax;
    if (ay) *ay = myIMU.ay;
    if (az) *az = myIMU.az;
}

void MPU::gyro(float* ax, float* ay, float* az)
{
    if (ax) *ax = myIMU.gx;
    if (ay) *ay = myIMU.gy;
    if (az) *az = myIMU.gz;
}

float MPU::mag()
{
    return ori;
}

float MPU::heading(void)
{
    return myIMU.yaw - this->heading_offset;
}

void MPU::reset_heading()
{
    this->heading_offset = myIMU.yaw;
}
