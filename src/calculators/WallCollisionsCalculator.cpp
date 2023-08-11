#include "WallCollisionsCalculator.h"
#include <math.h>

void WallCollisionsCalculator::updateParticles(std::vector<Particle> &particles, std::vector<Wall> &walls)
{
    pressure_last_frame = 0;
    for (Particle &particle : particles)
    {
        const int radius = particle.getRadius();
        const Vector particle_position = particle.getPosition();
        const Vector particle_velocity = particle.getVelocity();

        const float restistution = particle.getRestitution();

        for (Wall &wall : walls)
        {
            const direction wall_orientation = wall.getOrientation();
            const wallLimitType limit_type = wall.getLimitType();
            const int wall_position = wall.getPosition();
            const float wall_velocity = wall.getVelocity();

            Vector new_particle_position = particle_position;

            Vector new_particle_velocity = particle_velocity;

            int limit = 0;

            if (limit_type == min)
            {
                limit = wall_position + radius;
            }
            else
            {
                limit = wall_position - radius;
            }

            const int wall_length = wall.getLength();

            bool shouldBounce = false;

            shouldBounce = shouldParticleBounce(particle_position, limit, limit_type, wall_orientation, wall_length);

            if (shouldBounce)
            {
                const float time_increment = wall.getPreviousTimeSinceLastUpdated();

                const float particle_mass = particle.getMass();

                if (wall_orientation == x)
                {
                    new_particle_velocity.sety(calculateNewBounceVelocity(particle_velocity[1], restistution, wall_velocity));
                    new_particle_position.sety(calculateNewBouncePosition(particle_position[1], limit));
                    addPressureFromCollision(wall_length, time_increment, particle_mass, particle_velocity[1], new_particle_velocity[1]);
                }
                else
                {
                    new_particle_velocity.setx(calculateNewBounceVelocity(particle_velocity[0], restistution, wall_velocity));
                    new_particle_position.setx(calculateNewBouncePosition(particle_position[0], limit));
                    addPressureFromCollision(wall_length, time_increment, particle_mass, particle_velocity[0], new_particle_velocity[0]);
                }

                particle.setPosition(new_particle_position);
                particle.setVelocity(new_particle_velocity);
            }
        }
    }
}

bool WallCollisionsCalculator::shouldParticleBounce(Vector particle_position, int limit, wallLimitType limit_type, direction wall_orientation, int wall_length)
{

    if(wall_length == 0)
    {
        return false;
    }
    
    bool should_bounce = false;

    if (limit_type == min && wall_orientation == y)
    {
        if (particle_position[0] <= limit)
        {
            should_bounce = true;
        }
    }
    else if (limit_type == min && wall_orientation == x)
    {
        if (particle_position[1] <= limit)
        {
            should_bounce = true;
        }
    }
    else if (limit_type == max && wall_orientation == y)
    {
        if (particle_position[0] >= limit)
        {
            should_bounce = true;
        }
    }
    else if (limit_type == max && wall_orientation == x)
    {
        if (particle_position[1] >= limit)
        {
            should_bounce = true;
        }
    }

    return should_bounce;
}

float WallCollisionsCalculator::calculateNewBouncePosition(float old_position, float limit)
{
    const float displacement = limit - old_position;

    const float new_position = limit + displacement;

    return new_position;
}

float WallCollisionsCalculator::calculateNewBounceVelocity(float old_velocity, float restistution, float wall_velocity)
{
    const float new_velocity = -1 * old_velocity * restistution + wall_velocity;

    return new_velocity;
}

float WallCollisionsCalculator::getTemperature(std::vector<Particle> &particles) const
{
    double total_ke = 0;
    for (Particle &particle : particles)
    {
        const float speed = (particle.getVelocity()).getMagnitude();
        total_ke += 0.5 * speed * speed * particle.getMass();
    }

    const float K = 1000;
    const float temperature = total_ke / (particles.size() * K);

    return temperature;
}

float WallCollisionsCalculator::getPressureLastFrame() const
{
    return pressure_last_frame;
}

void WallCollisionsCalculator::addPressureFromCollision(
    int wall_length,
    float time_increment,
    int particle_mass,
    float velocity_before,
    float velocity_after)
{
    const float momentum_change = particle_mass * (velocity_after - velocity_before);

    float force = 0;
    if (time_increment > 0)
    {
        force = momentum_change / time_increment;
    }

    float pressure_from_collision = 0;
    if (wall_length > 0)
    {
        pressure_from_collision = abs(force / wall_length);
    }

    pressure_last_frame += pressure_from_collision;
}
