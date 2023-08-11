#include "MotionCalculator.h"

void MotionCalculator::calculateAngular(RotationalParticle &particle, const float dt)
{
    float angle = particle.getAngle();
    float velocity = particle.getVelocity_Angular();
    float acceleration = particle.getAcceleration_Angular();

    angle += velocity * dt + 0.5 * acceleration * dt * dt;
    particle.setAngle(angle);

    velocity += acceleration * dt;
    particle.setVelocity_Angular(velocity);
}

void MotionCalculator::calculateLinear(LinearParticle &particle, const float dt)
{
    Vector position = particle.getPosition();
    Vector velocity = particle.getVelocity();
    Vector acceleration = particle.getAcceleration();

    position += velocity * dt + 0.5 * acceleration * dt * dt;
    particle.setPosition(position);

    velocity += acceleration * dt;
    particle.setVelocity(velocity);
}
