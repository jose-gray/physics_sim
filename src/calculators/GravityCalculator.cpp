#include "GravityCalculator.h"

void GravityCalculator::updateForcesAndHandleCombinations(std::vector<Particle> &particles, Rocket &rocket)
{
    ParticleGrav(particles);
    ParticleCombinations(particles);
    RocketGrav(particles, rocket);
}

void GravityCalculator::ParticleGrav(std::vector<Particle> &particles)
{
    for (size_t i = 0; i < particles.size(); i++)
    {
        Force force;
        force.F = {0, 0};
        const Vector i_position = particles[i].getPosition();
        force.b = i_position;

        for (size_t j = 0; j < particles.size(); j++)
        {
            if (i != j)
            {
                NewtonsLaw(force, particles[i], particles[j]);
            }
        }
        particles[i].addForce(force);
    }
}

void GravityCalculator::RocketGrav(const std::vector<Particle> &particles, Rocket &rocket)
{
    Force force;
    force.b = rocket.getPosition();
    force.F = {0, 0};
    for (const Particle &particle : particles)
    {
        NewtonsLaw(force, rocket, particle);
    }

    rocket.addForce(force);
}

void GravityCalculator::NewtonsLaw(Force &force, const LinearParticle &particle, const LinearParticle &other_particle)
{
    const Vector i_x = particle.getPosition();
    const Vector j_x = other_particle.getPosition();
    const Vector dx = i_x - j_x;
    const float r = dx.getMagnitude();
    const float overlap_limit = 2;
    if (r > overlap_limit)
    {
        const float i_m = particle.getMass();
        const float j_m = other_particle.getMass();
        const float distance_cubed = pow(r, 3);
        force.F += dx * (-1 * G * i_m * j_m / distance_cubed);
    }
}

void GravityCalculator::ParticleCombinations(std::vector<Particle> &particles)
{
    std::vector<std::array<size_t, 2>> indices_to_combine;

    for (size_t i = 0; i < particles.size(); i++)
    {
        for (size_t j = 0; j < particles.size(); j++)
        {
            if (i != j && i < j)
            {
                const Vector i_x = particles[i].getPosition();
                const Vector j_x = particles[j].getPosition();
                const Vector dx = i_x - j_x;
                const float r = dx.getMagnitude();

                const int i_radius = particles[i].getRadius();
                const int j_radius = particles[j].getRadius();
                const float limit = i_radius + j_radius + 3;
                if (r <= limit)
                {
                    if (ShouldParticlesCombine(particles[i], particles[j], limit, r))
                    {
                        indices_to_combine.push_back({i, j});
                    }
                }
            }
        }
    }
    CombineFlaggedParticles(particles, indices_to_combine);
}

bool GravityCalculator::ShouldParticlesCombine(const LinearParticle &particle_i, const LinearParticle &particle_j, const float limit, const float r)
{
    const Vector i_v = particle_i.getVelocity();
    const Vector j_v = particle_j.getVelocity();

    const float i_m = particle_i.getMass();
    const float j_m = particle_j.getMass();
    const float total_m = i_m + j_m;

    const Vector i_p = i_m * i_v;
    const Vector j_p = j_m * j_v;
    const Vector total_p = i_p + j_p;

    const Vector i_v_zmf = i_v - total_p / (float)total_m;
    const Vector j_v_zmf = j_v - total_p / (float)total_m;

    const float i_speed_zmf = i_v_zmf.getMagnitude();
    const float j_speed_zmf = j_v_zmf.getMagnitude();

    const float i_KE_zmf = 0.5 * i_m * i_speed_zmf * i_speed_zmf;
    const float j_KE_zmf = 0.5 * j_m * j_speed_zmf * j_speed_zmf;

    const float KE_total_zmf = i_KE_zmf + j_KE_zmf;

    const float PE_to_escape_to_limit = (float)G * i_m * j_m * (1 / r - 1 / limit);

    return KE_total_zmf < PE_to_escape_to_limit;
}

void GravityCalculator::CombineFlaggedParticles(std::vector<Particle> &particles, std::vector<std::array<size_t, 2>> &indices_to_combine)
{
    removeDuplicateIndicies(indices_to_combine);

    for (size_t k = 0; k < indices_to_combine.size(); k++)
    {
        const int i = indices_to_combine[k][0];
        const int j = indices_to_combine[k][1];

        const float i_m = particles[i].getMass();
        const float j_m = particles[j].getMass();
        const float total_m = i_m + j_m;

        particles[i].setMass(total_m);

        const int i_radius = particles[i].getRadius();
        const int j_radius = particles[j].getRadius();

        const float i_r_cubed = pow(i_radius, 3);
        const float j_r_cubed = pow(j_radius, 3);

        const float radius_float = cbrt(i_r_cubed + j_r_cubed);
        const int radius_int = round(radius_float);

        particles[i].setRadius(radius_int);

        const Vector i_position = particles[i].getPosition();
        const Vector j_position = particles[j].getPosition();

        const Vector com = ((float)i_m / (total_m)) * i_position + ((float)j_m / (total_m)) * j_position;

        particles[i].setPosition(com);

        const Vector i_v = particles[i].getVelocity();
        const Vector j_v = particles[j].getVelocity();

        const Vector i_p = i_m * i_v;
        const Vector j_p = j_m * j_v;
        const Vector total_p = i_p + j_p;

        particles[i].setVelocity(total_p / total_m);

        const Vector i_a = particles[i].getAcceleration();
        const Vector j_a = particles[j].getAcceleration();

        const Vector mass_weighted_a = (i_a * i_m + j_a * j_m) / total_m;

        particles[i].setAcceleration(mass_weighted_a);

        const std::vector<Force> j_forces = particles[j].getForces();

        for (Force force : j_forces)
        {
            particles[i].addForce(force);
        }

        particles.erase(particles.begin() + j);
    }
}

void GravityCalculator::removeDuplicateIndicies(std::vector<std::array<size_t, 2>> &indices_to_combine)
{
    std::vector<int> duplicated_indices;

    for (size_t i = 0; i < indices_to_combine.size(); i++)
    {
        const std::array<size_t, 2> indices_i = indices_to_combine[i];

        for (size_t j = 0; j < indices_to_combine.size(); j++)
        {
            const std::array<size_t, 2> indices_j = indices_to_combine[j];

            bool matching = (indices_i[0] == indices_j[1]) && (indices_i[1] == indices_j[0]);

            if (matching)
            {
                duplicated_indices.push_back(j);
            }
        }
    }

    for (size_t i = 0; i < duplicated_indices.size(); i++)
    {
        indices_to_combine.erase(indices_to_combine.begin() + duplicated_indices[i]);
    }
}
