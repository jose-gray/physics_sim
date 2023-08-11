#ifndef LinearParticle_H
#define LinearParticle_H

#include "../Force.h"
#include "../Vector.h"
#include "math.h"
#include <iostream>
#include <vector>

class LinearParticle
{
private:
    Vector position;
    Vector velocity;
    Vector acceleration;
    Vector display_position;
    std::vector<Force> forces;
    float mass;
    float time_last_updated;
    bool time_has_been_set;

public:
    LinearParticle();

    void setPosition(const Vector input_position)
    {
        position = input_position;
    };
    void setPosition(const float x, const float y)
    {
        position = {x, y};
    };
    Vector getPosition() const
    {
        return position;
    };

    void setVelocity(const Vector inputVelocity)
    {
        velocity = inputVelocity;
    };
    void setVelocity(const float x, const float y)
    {
        velocity = {x, y};
    };
    Vector getVelocity() const
    {
        return velocity;
    };

    void setAcceleration(const Vector input_acceleration)
    {
        acceleration = input_acceleration;
    };
    void setAcceleration(const float x, const float y)
    {
        acceleration = {x, y};
    };
    Vector getAcceleration() const
    {
        return acceleration;
    };

    void setDisplayPosition(const Vector input_position)
    {
        display_position = input_position;
    };
    void setDisplayPosition(const float x, const float y)
    {
        display_position = {x, y};
    };
    Vector getDisplayPosition() const
    {
        return display_position;
    };

    std::vector<Force> getForces() const
    {
        return forces;
    };
    void addForce(const Force input_force)
    {
        forces.push_back(input_force);
    };
    void resetForces()
    {
        forces.clear();
    };

    void setMass(const int input_mass)
    {
        mass = input_mass;
    };
    float getMass() const
    {
        return mass;
    };

    void setTimeLastUpdated(float time_now);
    float getTimeSinceLastUpdated(float time_now) const;
    float getTimeLastUpdated() const;
};

bool operator==(const LinearParticle &lhs, const LinearParticle &rhs);

bool operator!=(const LinearParticle &lhs, const LinearParticle &rhs);

std::ostream &operator<<(std::ostream &os, const LinearParticle &particle);

#endif
