#ifndef MOTIONCALCULATOR_H
#define MOTIONCALCULATOR_H

#include "../objects/RotationalParticle.h"

class MotionCalculator
{
public:
    void calculateAngular(RotationalParticle &particle, const float dt);
    void calculateLinear(LinearParticle &particle, const float dt);

private:

};

#endif