#ifndef ROCKET_DATA_CALCULATOR_H
#define ROCKET_DATA_CALCULATOR_H

#include "../objects/RocketData.h"
#include "../objects/Rocket.h"
#include "../objects/LinearParticle.h"

#pragma GCC diagnostic ignored "-Wunused-function"

namespace RocketDataCalculator
{
    static void updateRocketData(RocketData &rocket_data, const Rocket &rocket, const LinearParticle &center_particle)
    {
        const Vector x_rocket = rocket.getPosition();
        const Vector x_particle = center_particle.getPosition();
        const Vector x_rel = x_rocket - x_particle;
        rocket_data.displacement = x_rel;

        const Vector v_rocket = rocket.getVelocity();
        const Vector v_particle = center_particle.getVelocity();
        const Vector v_rel = v_rocket - v_particle;
        rocket_data.velocity = v_rel;
    }
};

#endif