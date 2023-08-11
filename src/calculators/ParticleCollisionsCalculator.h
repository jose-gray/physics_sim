#include "../objects/Particle.h"

class ParticleCollisionsCalculator
{
public:
    void updateParticles(std::vector<Particle> &particles);

private:
    const Vector unit_vector = {1, 1};

    int i_radius;
    int j_radius;

    Vector i_position;
    Vector j_position;

    int range;

    Vector displacement;

    float distance;

    float overlap_magnitude;

    float i_m;
    float j_m;
    float total_m;

    Vector i_velocity;
    Vector j_velocity;

    void updateInitialVariables(std::vector<Particle> &particles, size_t i, size_t j);

    void updateCollisionVariables(std::vector<Particle> &particles, size_t i, size_t j);

    void updatePosition(std::vector<Particle> &particles, size_t i, size_t j);

    void updateVelocity(std::vector<Particle> &particles, size_t i, size_t j);
};
