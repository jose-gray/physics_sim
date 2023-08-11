#ifndef ANGULAR_ACCELERATION_CALCULATOR_H
#define ANGULAR_ACCELERATION_CALCULATOR_H

#include "../objects/RotationalParticle.h"

class AccelerationCalculator
{
public:
    void calculateAngular(RotationalParticle &particle);
    void calculateLinear(LinearParticle &particle);

private:

};

#endif