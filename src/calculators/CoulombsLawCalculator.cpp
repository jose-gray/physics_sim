#include "CoulombsLawCalculator.h"

void CoulombsLawCalculator::updateParticles(std::vector<Particle> &particles)
{
    for (size_t i = 0; i < particles.size(); i++)
    {
        const Vector i_position = particles[i].getPosition();


        Vector E = {0, 0};

        for (size_t j = 0; j < particles.size(); j++)
        {
            if (i != j)
            {
                const Vector j_position = particles[j].getPosition();

                const Vector displacement = i_position - j_position;

                const float j_q = particles[j].getCharge();

                const float distance = displacement.getMagnitude();
                const float distance_cubed = pow(distance, 3);

                const float permitivity = 0.000000001;

                if (distance_cubed > 8) // fudge to avoid overlap errors in case of double bounce
                {
                    E += displacement * (j_q / (distance_cubed * permitivity)); // Coloumbs law
                }
            }
        }
        const float i_q = particles[i].getCharge();

        Force force;
        force.F = E * i_q;
        force.b = i_position;

        particles[i].addForce(force);
    }
}