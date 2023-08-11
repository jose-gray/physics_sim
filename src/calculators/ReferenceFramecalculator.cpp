#include "ReferenceFrameCalculator.h"

void ReferenceFrameCalculator::changeToRocketFrame(Objects &objects)
{
    Vector displacement = center - objects.rocket.getPosition();

    objects.rocket.setPosition(center);

    for (Particle &particle : objects.particles)
    {
        const Vector original_position_particle = particle.getPosition();

        particle.setPosition(original_position_particle + displacement);
    }

    for (Dot &dot : objects.dot_data.dots)
    {
        const Vector original_position_dot = dot.getPosition();
        dot.setPosition(original_position_dot + displacement);
    }

    displacement.rotateVector(-1 * cumulativeAngleOfRotation); // todo why -1?
    cumulativeDisplacement += displacement;

    const float angle_to_verticle = -1 * objects.rocket.getAngle();

    rotation_calculator.rotateParticleAboutPoint(center, angle_to_verticle, objects.rocket);

    for (Particle &particle : objects.particles)
    {
        rotation_calculator.rotateParticleAboutPoint(center, angle_to_verticle, particle);
    }

    for (Dot &dot : objects.dot_data.dots)
    {
        rotation_calculator.rotateParticleAboutPoint(center, angle_to_verticle, dot);
    }

    cumulativeAngleOfRotation += angle_to_verticle;
}

void ReferenceFrameCalculator::changeToUniverseFrame(Objects &objects)
{
    changeToRocketFrame(objects);

    rotation_calculator.rotateParticleAboutPoint(center, -1 * cumulativeAngleOfRotation, objects.rocket);
    for (Particle &particle : objects.particles)
    {
        rotation_calculator.rotateParticleAboutPoint(center, -1 * cumulativeAngleOfRotation, particle);
    }
    for (Dot &dot : objects.dot_data.dots)
    {
        rotation_calculator.rotateParticleAboutPoint(center, -1 * cumulativeAngleOfRotation, dot);
    }
    cumulativeAngleOfRotation = 0;

    const Vector original_position_rocket = objects.rocket.getPosition();
    objects.rocket.setPosition(original_position_rocket - cumulativeDisplacement);
    for (Particle &particle : objects.particles)
    {
        const Vector original_particle_position = particle.getPosition();
        particle.setPosition(original_particle_position - cumulativeDisplacement);
    }
    for (Dot &dot : objects.dot_data.dots)
    {
        const Vector original_position_dot = dot.getPosition();
        dot.setPosition(original_position_dot - cumulativeDisplacement);
    }
    cumulativeDisplacement = {0, 0};
}