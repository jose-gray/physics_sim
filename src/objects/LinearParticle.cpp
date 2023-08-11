#include "LinearParticle.h"

LinearParticle::LinearParticle()
{
    position = {0, 0};
    velocity = {0, 0};
    acceleration = {0, 0};
    time_has_been_set = false;
    time_last_updated = 0;
    mass = 1;
}

float LinearParticle::getTimeSinceLastUpdated(float time_now) const
{
    float time_since_last_update = 0;

    if (time_has_been_set)
    {
        time_since_last_update = time_now - time_last_updated;
    }

    return time_since_last_update;
}

float LinearParticle::getTimeLastUpdated() const
{
    return time_last_updated;
}

void LinearParticle::setTimeLastUpdated(float time_now)
{
    time_has_been_set = true;
    time_last_updated = time_now;
}

bool operator==(const LinearParticle &lhs, const LinearParticle &rhs)
{
    return lhs.getPosition() == rhs.getPosition() &&
           lhs.getVelocity() == rhs.getVelocity() &&
           lhs.getAcceleration() == rhs.getAcceleration() &&
           lhs.getMass() == rhs.getMass() &&
           lhs.getDisplayPosition() == rhs.getDisplayPosition() &&
           lhs.getForces() == rhs.getForces();
}

bool operator!=(const LinearParticle &lhs, const LinearParticle &rhs)
{
    return !(lhs == rhs);
}

std::ostream &operator<<(std::ostream &os, const LinearParticle &particle)
{
    os << "x: " << particle.getPosition() << "\n"
       << "v: " << particle.getVelocity() << "\n"
       << "a: " << particle.getAcceleration() << "\n"
       << "m: " << particle.getMass() << "\n"
       << "disp_x: " << particle.getDisplayPosition() << "\n"
       << "Forces: ";

    for (Force force : particle.getForces())
    {
        os << "\n   "<< force;
    }

    os << "\n";

    return os;
}
