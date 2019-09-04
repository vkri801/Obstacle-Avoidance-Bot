/*! \file
    \brief Implementation of the Integrator class.
    \see Integrator
*/

#include "Integrator.h"
#include "utils.h"

Integrator::Integrator() :
    t1(Utils::seconds()),
    f1(0),
    val(0)
{
}

float Integrator::update(float f0)
{
    float t0 = Utils::seconds();
    float dt = t0 - this->t1;
    this->val += 0.5 * (f0 + f1) *dt;

    this->t1 = t0;
    this->f1 = f0;

    return this->val;
}

float Integrator::value()
{
    return this->val;
}

void Integrator::reset()
{
    this->val = 0;
}

