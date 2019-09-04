/*! \file
    \brief Implementation of the Firehose class.
    \see Firehose
*/

#include "Firehose.h"
#include <Arduino.h>

#include "PARAMETERS.h"
#include "PIN_DEFINES.h"

#include "utils.h"

Firehose::Firehose() :
    port(PORT_PT_PIN),
    star(STAR_PT_PIN)
{
    serlog("init firehose\n");

    this->fan_pin = FIREHOSE_FAN_PIN;
    this->servo_pos = 1500;

    pinMode(this->fan_pin, OUTPUT);
    pinMode(FIREHOSE_SERVO_PIN, OUTPUT);
    this->servo.attach(FIREHOSE_SERVO_PIN);
}


Firehose::~Firehose()
{
    pinMode(this->fan_pin, INPUT);
    this->servo.detach();
}


bool Firehose::fire_detected()
{
    int port = this->port.read_raw();
    int star = this->star.read_raw();

    serlog("pt reading: ");
    serlog(port + star);
    serlog("\n");

    return
        port > FIREHOSE_FIRE_DETECTION_THRESHOLD ||
        star > FIREHOSE_FIRE_DETECTION_THRESHOLD;
}


bool Firehose::track_fire()
{
    int diff = this->port.read_raw() - this->star.read_raw();
    if (abs(diff) < FIREHOSE_FAN_FACING_FIRE_THRESHOLD) return true;

    int delta = FIREHOSE_TRACKING_GAIN * diff;

    this->servo_pos += delta;
    this->servo.writeMicroseconds(this->servo_pos);

    return false;
}

void Firehose::on()
{
    digitalWrite(this->fan_pin, HIGH);
}

void Firehose::off()
{
    digitalWrite(this->fan_pin, LOW);
}


void Firehose::reset_servo_pos()
{
    this->servo_pos = 1500;
    this->servo.writeMicroseconds(this->servo_pos);
}
