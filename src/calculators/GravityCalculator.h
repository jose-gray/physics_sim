#include "../objects/Particle.h"
#include "../objects/Rocket.h"

#include <array>
#include <vector>

class GravityCalculator
{
public:
    void updateForcesAndHandleCombinations(std::vector<Particle> &particles, Rocket &rocket);

private:
    const int G = 1;
    void RocketGrav(const std::vector<Particle> &particles, Rocket &rocket);
    void ParticleGrav(std::vector<Particle> &particles);
    void NewtonsLaw(Force &force, const LinearParticle &particle, const LinearParticle &other_particle);
    void ParticleCombinations(std::vector<Particle> &particles);
    bool ShouldParticlesCombine(const LinearParticle &particle_i, const LinearParticle &particle_j, const float limit, const float r);
    void CombineFlaggedParticles(std::vector<Particle> &particles, std::vector<std::array<size_t, 2>> &indices_to_combine);
    void removeDuplicateIndicies(std::vector<std::array<size_t, 2>> &indices_to_combine);
};