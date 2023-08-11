#ifndef NEWTONIAN_CALCULATOR_H
#define NEWTONIAN_CALCULATOR_H

#include "../objects/Objects.h"
#include "AccelerationCalculator.h"
#include "MotionCalculator.h"

class NewtonianCalculator
{
public:
    void updateRocket(Rocket &rocket, float time_now);
    void updateParticles(std::vector<Particle> &particles, float time_now);

private:
    AccelerationCalculator acceleration_calculator;
    MotionCalculator motion_calculator;
};

#endif