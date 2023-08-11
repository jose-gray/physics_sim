#include "NewtonianCalculator.h"

void NewtonianCalculator::updateRocket(Rocket &rocket, float time_now)
{
    acceleration_calculator.calculateAngular(rocket);
    acceleration_calculator.calculateLinear(rocket);

    const float dt = rocket.getTimeSinceLastUpdated(time_now);

    motion_calculator.calculateAngular(rocket, dt);
    motion_calculator.calculateLinear(rocket, dt);

    rocket.setTimeLastUpdated(time_now);
    rocket.resetForces();
}

void NewtonianCalculator::updateParticles(std::vector<Particle> &particles, float time_now)
{
    for (Particle &particle : particles)
    {
        acceleration_calculator.calculateLinear(particle);

        const float dt = particle.getTimeSinceLastUpdated(time_now);

        motion_calculator.calculateLinear(particle, dt);

        particle.setTimeLastUpdated(time_now);

        particle.resetForces();
    }
}
