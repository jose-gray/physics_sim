#pragma once
#include "../objects/Particle.h"
#include  "../objects/Wall.h"

class WallCollisionsCalculator
{
public:
    void updateParticles(std::vector<Particle> &particles, std::vector<Wall> &walls);

    float getTemperature(std::vector<Particle> &particles) const;

    float getPressureLastFrame() const;

private:
    bool shouldParticleBounce(Vector particle_position, int limit, wallLimitType limit_type, direction wall_orientation, int wall_length);

    float calculateNewBouncePosition(float old_position, float limit);

    float calculateNewBounceVelocity(float old_velocity, float restistution, float wall_velocity);

    float pressure_last_frame;

    void addPressureFromCollision(int wall_length, float time_increment, int particle_mass,  float velocity_before, float velocity_after);
};