#include "RotationCalculator.h"

void RotationCalculator::rotateParticleAboutPoint(Vector center_of_rotation, float angle, LinearParticle &particle)
{
    const Vector position = particle.getPosition();

    Vector displacement = position - center_of_rotation;
    Vector velocity = particle.getVelocity();
    Vector acceleration = particle.getAcceleration();

    displacement.rotateVector(angle);
    velocity.rotateVector(angle);
    acceleration.rotateVector(angle);

    particle.setPosition(center_of_rotation + displacement);
    particle.setVelocity(velocity);
    particle.setAcceleration(acceleration);
}

void RotationCalculator::rotateParticleAboutPoint(Vector center_of_rotation, float cos_angle, float sin_angle, LinearParticle &particle)
{
    const Vector position = particle.getPosition();

    Vector displacement = position - center_of_rotation;
    Vector velocity = particle.getVelocity();
    Vector acceleration = particle.getAcceleration();

    displacement.rotateVector(cos_angle, sin_angle);
    velocity.rotateVector(cos_angle, sin_angle);
    acceleration.rotateVector(cos_angle, sin_angle);

    particle.setPosition(center_of_rotation + displacement);
    particle.setVelocity(velocity);
    particle.setAcceleration(acceleration);
}

void RotationCalculator::rotateParticleAboutPoint(Vector center_of_rotation, float angle, Dot &dot)
{
    const Vector position = dot.getPosition();

    Vector displacement = position - center_of_rotation;

    displacement.rotateVector(angle);

    dot.setPosition(center_of_rotation + displacement);
}

void RotationCalculator::rotateParticleAboutPoint(Vector center_of_rotation, float cos_angle, float sin_angle, Dot &dot)
{
    const Vector position = dot.getPosition();

    Vector displacement = position - center_of_rotation;

    displacement.rotateVector(cos_angle, sin_angle);

    dot.setPosition(center_of_rotation + displacement);
}

void RotationCalculator::rotateParticleAboutPoint(Vector center_of_rotation, float angle, RotationalParticle &particle)
{
    const Vector position = particle.getPosition();

    Vector displacement = position - center_of_rotation;
    Vector velocity = particle.getVelocity();
    Vector acceleration = particle.getAcceleration();

    displacement.rotateVector(angle);
    velocity.rotateVector(angle);
    acceleration.rotateVector(angle);

    particle.setPosition(center_of_rotation + displacement);
    particle.setVelocity(velocity);
    particle.setAcceleration(acceleration);

    const float particle_angle = particle.getAngle();
    particle.setAngle(particle_angle + angle);
}
