#include "Particle.h"
#include <math.h>

Particle::Particle()
{
    radius = 1;
    display_radius = radius;
    charge = 0;
    is_fixed = false;
    coefficient_of_restitution = 1;
}

void Particle::setCharge(const float input_charge)
{
    charge = input_charge;
    if (charge < 0)
    {
        particle_color = BLUE;
    }
    else if (charge > 0)
    {
        particle_color = RED;
    }
}

bool operator==(const Particle &lhs, const Particle &rhs)
{
    return (LinearParticle)lhs == (LinearParticle)rhs &&
           lhs.getRadius() == rhs.getRadius() &&
           lhs.getRestitution() == rhs.getRestitution() &&
           lhs.getCharge() == rhs.getCharge() &&
           lhs.getIsFixed() == rhs.getIsFixed() &&
           lhs.getDisplayRadius() == rhs.getDisplayRadius();
}

