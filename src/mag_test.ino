#ifdef MAG_TEST

#include <Arduino.h>
#include "MPU.h"

MPU* mpu;

HardwareSerial* SerialCom;

int TABLEVEL = 0;

void setup()
{
    SerialCom = &Serial1;
    SerialCom->begin(115200);

    mpu = new MPU();
}

unsigned int i = 0;
float avgx = 0;
float avgy = 0;
float avgz = 0;

extern bool aligned_to_track(void);

void loop()
{
    mpu->update();

    // testing
    float mx, my, mz;
    mpu->mag(&mx, &my, &mz);

    SerialCom->print(mx, 6); SerialCom->print(" ");
    SerialCom->print(my, 6); SerialCom->print(" ");  
    SerialCom->print(mz, 6); SerialCom->print(" ");

    /* ++i; */
    /* avgx += mx; */
    /* avgy += my; */
    /* avgz += mz; */

    /* SerialCom->print(avgx/i, 6); SerialCom->print(" "); */
    /* SerialCom->print(avgy/i, 6); SerialCom->print(" "); */  
    /* SerialCom->print(avgz/i, 6); SerialCom->print(" "); */
    /* SerialCom->print(i); SerialCom->print(" "); */

    SerialCom->print("\n");

    /* aligned_to_track(); */
}

#endif
