/*! \file
    \brief Implementation of the Differentiator class.
    \see Differentiator
*/

#include "Differentiator.h"
#include "utils.h"

Differentiator::Differentiator() :
    t1(Utils::seconds()),
    f1(0),
    val(0)
{
}

float Differentiator::update(float f0)
{
    float t0 = Utils::seconds();
    this->val = (f0 - this->f1) / (t0 - this->t1);

    this->f1 = f0;
    this->t1 = t0;

    return this->val;
}

float Differentiator::value()
{
    return this->val;
}

