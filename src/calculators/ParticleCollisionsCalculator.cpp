#include "ParticleCollisionsCalculator.h"

void ParticleCollisionsCalculator::updateParticles(std::vector<Particle> &particles)
{
    for (size_t i = 0; i < particles.size(); i++)
    {
        for (size_t j = i + 1; j < particles.size(); j++)
        {
            updateInitialVariables(particles, i, j);

            bool is_collision = overlap_magnitude > 0;

            if (distance == 0)
            {
                is_collision = false; // safety for initialising at same pos
            }

            if (particles[i].getIsFixed() && particles[j].getIsFixed())
            {
                is_collision = false; // stop fixed particles from running around
            }

            if (is_collision)
            {
                updateCollisionVariables(particles, i, j);

                if (i_m == 0 || j_m == 0)
                {
                    break; // saftey for zero mass
                }

                updatePosition(particles, i, j);

                updateVelocity(particles, i, j);
            }
        }
    }
}

void ParticleCollisionsCalculator::updateInitialVariables(std::vector<Particle> &particles, size_t i, size_t j)
{
    i_radius = particles[i].getRadius();
    j_radius = particles[j].getRadius();

    i_position = particles[i].getPosition();
    j_position = particles[j].getPosition();

    range = i_radius + j_radius;

    displacement = i_position - j_position;

    distance = displacement.getMagnitude();

    overlap_magnitude = range - distance;
}

void ParticleCollisionsCalculator::updateCollisionVariables(std::vector<Particle> &particles, size_t i, size_t j)
{
    i_m = particles[i].getMass();
    j_m = particles[j].getMass();
    total_m = i_m + j_m;

    i_velocity = particles[i].getVelocity();
    j_velocity = particles[j].getVelocity();
}

void ParticleCollisionsCalculator::updatePosition(std::vector<Particle> &particles, size_t i, size_t j)
{
    Vector offset = displacement * (overlap_magnitude / distance); // similar triangles

    offset += unit_vector * 0.000001; // to prevent getting stuck

    i_position += offset * j_m / total_m;
    j_position += offset * -1 * i_m / total_m; // larger offset for smaller mass

    particles[i].setPosition(i_position);
    particles[j].setPosition(j_position);
}

void ParticleCollisionsCalculator::updateVelocity(std::vector<Particle> &particles, size_t i, size_t j)
{
    const float e = (particles[i].getRestitution() + particles[j].getRestitution()) / 2;

    const float cos_angle = displacement[0] / distance;
    const float sin_angle = -1 * displacement[1] / distance;

    // rotate to frame along line of collision
    i_velocity.rotateVector(cos_angle, sin_angle);
    j_velocity.rotateVector(cos_angle, sin_angle);

    // cons momentum parallel to collision
    // coefficient of rest. (or cons energy if e=1) along line of collision
    // no change perp to collision
    const float i_velocity_parallel_after = ((i_m - j_m * e) * i_velocity[0] + (1 + e) * j_m * j_velocity[0]) / (total_m);
    const float j_velocity_parallel_after = ((j_m - i_m * e) * j_velocity[0] + (1 + e) * i_m * i_velocity[0]) / (total_m);

    i_velocity.setx(i_velocity_parallel_after);
    j_velocity.setx(j_velocity_parallel_after);

    // rotate back
    i_velocity.rotateVector(cos_angle, -1 * sin_angle);
    j_velocity.rotateVector(cos_angle, -1 * sin_angle);

    particles[i].setVelocity(i_velocity);
    particles[j].setVelocity(j_velocity);
}
