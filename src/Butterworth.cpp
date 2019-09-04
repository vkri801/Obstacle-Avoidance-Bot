#include "Butterworth.h"

float b[] = { 0.0029,  0.0087, 0.0087,  0.0029 };
float a[] = { 1.0000, -2.3741, 1.9294, -0.5321 };

float Butterworth::update(float e)
{
    this->e[3] = this->e[2];
    this->e[2] = this->e[1];
    this->e[0] = e;


}
