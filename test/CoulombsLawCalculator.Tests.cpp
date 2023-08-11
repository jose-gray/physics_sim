#include <gtest/gtest.h>

#include "../src/calculators/CoulombsLawCalculator.h"

TEST(coulombs_law, two_postives_repel)
{
    // setup
    std::vector<Particle> particles;
    particles.resize(2);
    CoulombsLawCalculator coulombs_law_calculator;

    // given
    particles[0].setPosition(200, 200);
    particles[0].setCharge(1);

    particles[1].setPosition(210, 200);
    particles[1].setCharge(1);

    // when
    coulombs_law_calculator.updateParticles(particles);

    // then particles given force
    // particle 0
    Force expected_force;
    expected_force.F = {-1e+07, 0}; // Coulomb said this
    expected_force.b = {200, 200};
    std::vector<Force> expected_forces = {expected_force};

    std::vector<Force> actual_forces = particles[0].getForces();
    EXPECT_EQ(expected_forces, actual_forces);

    // particle 1
    expected_force;
    expected_force.F = {1e+07, 0}; // Coulomb said this
    expected_force.b = {210, 200};
    expected_forces = {expected_force};

    actual_forces = particles[1].getForces();
    EXPECT_EQ(expected_forces, actual_forces);
}

TEST(coulombs_law, negative_and_positive_attracts)
{
    // setup
    std::vector<Particle> particles;
    particles.resize(2);
    CoulombsLawCalculator coulombs_law_calculator;

    // given
    particles[0].setPosition(200, 200);
    particles[0].setCharge(1);

    particles[1].setPosition(210, 200);
    particles[1].setCharge(-1);

    // when
    coulombs_law_calculator.updateParticles(particles);

    // then particles given force
    // particle 0
    Force expected_force;
    expected_force.F = {1e+07, 0}; // Coulomb said this
    expected_force.b = {200, 200};
    std::vector<Force> expected_forces = {expected_force};

    std::vector<Force> actual_forces = particles[0].getForces();
    EXPECT_EQ(expected_forces, actual_forces);

    // particle 1
    expected_force;
    expected_force.F = {-1e+07, 0}; // Coulomb said this
    expected_force.b = {210, 200};
    expected_forces = {expected_force};

    actual_forces = particles[1].getForces();
    EXPECT_EQ(expected_forces, actual_forces);
}