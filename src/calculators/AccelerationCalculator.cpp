#include "AccelerationCalculator.h"

void AccelerationCalculator::calculateAngular(RotationalParticle &particle)
{
    float acceleration_angular = 0;

    for (Force force : particle.getForces())
    {
        Vector com_to_force = force.b - particle.getCom();
        acceleration_angular += crossProduct(com_to_force, force.F) / particle.getI();
    }

    particle.setAcceleration_Angular(acceleration_angular);
}

void AccelerationCalculator::calculateLinear(LinearParticle &particle)
{
    Vector a = {0, 0};

    for (Force force : particle.getForces())
    {
        a += (1 / particle.getMass()) * force.F;
    }

    particle.setAcceleration(a);
}
