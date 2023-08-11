#include <gtest/gtest.h>

#include "../src/calculators/NewtonianCalculator.h"

class NewtonianCalculator_Fixture : public ::testing::Test
{
protected:
    NewtonianCalculator calculator;

    const float time_now = 10;

    std::vector<Particle> particles;

    Rocket rocket;
};

TEST_F(NewtonianCalculator_Fixture, time_reset_particles)
{
    // Given
    particles.resize(1);

    // When
    calculator.updateParticles(particles, time_now);

    // Then
    const float time_last_updated = particles[0].getTimeLastUpdated();

    ASSERT_EQ(time_now, time_last_updated);
}

TEST_F(NewtonianCalculator_Fixture, force_reset_particles)
{
    // Given
    particles.resize(1);

    Force force;
    force.F = {10, 5};
    force.b = {100, 20};
    particles[0].addForce(force);

    // When
    calculator.updateParticles(particles, time_now);

    // then
    std::vector<Force> forces = particles[0].getForces();
    std::vector<Force> empty_vector = {};

    ASSERT_EQ(empty_vector, forces);
}

TEST_F(NewtonianCalculator_Fixture, time_reset_rocket)
{
    // Given

    // When
    calculator.updateRocket(rocket, time_now);

    // Then
    const float time_last_updated = rocket.getTimeLastUpdated();

    ASSERT_EQ(time_now, time_last_updated);
}

TEST_F(NewtonianCalculator_Fixture, force_reset_rocket)
{
    // Given
    Force force;
    force.F = {10, 5};
    force.b = {100, 20};
    rocket.addForce(force);

    // When
    calculator.updateRocket(rocket, time_now);

    // then
    std::vector<Force> forces = rocket.getForces();
    std::vector<Force> empty_vector = {};

    ASSERT_EQ(empty_vector, forces);
}