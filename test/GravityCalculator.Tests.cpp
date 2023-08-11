#include <gtest/gtest.h>

#include "../src/calculators/GravityCalculator.h"
#include <math.h>

class gravityCalculatorFixture : public ::testing::Test
{
protected:
    std::vector<Particle> particles;
    Rocket rocket;
    GravityCalculator gravity_calculator;
};

TEST_F(gravityCalculatorFixture, two_particles_attract_same_mass)
{
    // setup
    particles.resize(2);

    // given
    particles[0].setMass(8);
    particles[0].setPosition(200, 200);

    particles[1].setMass(8);
    particles[1].setPosition(210, 200);

    // when
    gravity_calculator.updateForcesAndHandleCombinations(particles, rocket);

    // then particles given force acting on position
    // particle 0
    Force expected_force;
    expected_force.F = {0.64, 0}; // Newton said this
    expected_force.b = {200, 200};
    std::vector<Force> expected_forces = {expected_force};

    std::vector<Force> actual_forces = particles[0].getForces();

    EXPECT_EQ(expected_forces, actual_forces);

    // particle 1
    expected_force;
    expected_force.F = {-0.64, 0}; // Newton said this
    expected_force.b = {210, 200};
    expected_forces = {expected_force};

    actual_forces = particles[1].getForces();

    EXPECT_EQ(expected_forces, actual_forces);
}

TEST_F(gravityCalculatorFixture, two_particles_attract_different_mass)
{
    // setup
    particles.resize(2);

    // given
    particles[0].setMass(8);
    particles[0].setPosition(200, 200);

    particles[1].setMass(64);
    particles[1].setPosition(210, 200);

    // when
    gravity_calculator.updateForcesAndHandleCombinations(particles, rocket);

    // then particles given force acting on position
    // particle 0
    Force expected_force;
    expected_force.F = {5.12, 0}; // Newton said this
    expected_force.b = {200, 200};
    std::vector<Force> expected_forces = {expected_force};

    std::vector<Force> actual_forces = particles[0].getForces();

    EXPECT_EQ(expected_forces, actual_forces);

    // particle 1
    expected_force;
    expected_force.F = {-5.12, 0}; // Newton said this
    expected_force.b = {210, 200};
    expected_forces = {expected_force};

    actual_forces = particles[1].getForces();

    EXPECT_EQ(expected_forces, actual_forces);
}

void setupTwoParticlesThatShouldCombine_ZMF(std::vector<Particle> &particles)
{
    // given
    particles.resize(3);

    const int start_position = 50;

    const int radius_0 = 10;
    const int radius_1 = 9;
    const int position_1 = start_position + radius_0 + radius_1 + 1; // edges 1 apart

    const int mass_0 = 10;
    const int mass_1 = 100;

    const Vector velocity_0 = {0.5, 0};
    const Vector velocity_1 = {-0.05, 0}; // gives zero total p

    particles[0].setMass(10);
    particles[0].setRadius(radius_0);
    particles[0].setPosition(start_position, start_position);
    particles[0].setVelocity(velocity_0);

    particles[1].setMass(100);
    particles[1].setRadius(radius_1);
    particles[1].setPosition(position_1, start_position);
    particles[1].setVelocity(velocity_1);

    particles[2].setMass(50);
    particles[2].setRadius(20);
    particles[2].setPosition(start_position, start_position + 50);
    particles[2].setVelocity(13, 14);
}

TEST_F(gravityCalculatorFixture, particleCombination_MassGivenToParticle0)
{
    // Given
    setupTwoParticlesThatShouldCombine_ZMF(particles);

    // When
    gravity_calculator.updateForcesAndHandleCombinations(particles, rocket);

    // Then
    const float total_mass = 110;

    const float actual_particle_0_mass = particles[0].getMass();

    ASSERT_EQ(total_mass, actual_particle_0_mass);
}

TEST_F(gravityCalculatorFixture, particleCombination_SizeVolumeToParticle0)
{
    // Given
    setupTwoParticlesThatShouldCombine_ZMF(particles);

    // When
    gravity_calculator.updateForcesAndHandleCombinations(particles, rocket);

    // Then
    const int expected_radius = 12; // rounded (cbrt(10^3 + 9^3))

    const int actual_particle_0_radius = particles[0].getRadius();

    ASSERT_EQ(expected_radius, actual_particle_0_radius);
}

TEST_F(gravityCalculatorFixture, particleCombination_PositionConservingCOMGivenToParticle0)
{
    // Given
    setupTwoParticlesThatShouldCombine_ZMF(particles);

    // When
    gravity_calculator.updateForcesAndHandleCombinations(particles, rocket);

    // Then
    const float expected_position = 68.18181818; // COM

    const float actual_particle_0_position = particles[0].getPosition()[0];

    ASSERT_EQ(expected_position, actual_particle_0_position);
}

TEST_F(gravityCalculatorFixture, particleCombination_VelocityConservingMomentumGivenToParticle0)
{
    // Given
    setupTwoParticlesThatShouldCombine_ZMF(particles);

    // When
    gravity_calculator.updateForcesAndHandleCombinations(particles, rocket);

    // Then
    const float expected_velocity = 0; // NL3

    const float actual_particle_0_velocity = particles[0].getVelocity()[0];

    ASSERT_EQ(expected_velocity, actual_particle_0_velocity);
}

TEST_F(gravityCalculatorFixture, particleCombination_Particle1ReplacedWithParticle2)
{
    // Given
    setupTwoParticlesThatShouldCombine_ZMF(particles);

    // When
    gravity_calculator.updateForcesAndHandleCombinations(particles, rocket);

    // Then
    Particle expected_particle;

    expected_particle.setMass(50);
    expected_particle.setRadius(20);
    expected_particle.setPosition(50, 100);
    expected_particle.setVelocity(13, 14);
    Force expected_force;
    expected_force.F = {0.640329, -1.80082};
    expected_force.b = {50, 100};
    expected_particle.addForce(expected_force);

    ASSERT_EQ(expected_particle, particles[1]); // todo just use a vector pls
}

TEST_F(gravityCalculatorFixture, particleCombination_countReduced)
{
    // Given
    setupTwoParticlesThatShouldCombine_ZMF(particles);

    // When
    gravity_calculator.updateForcesAndHandleCombinations(particles, rocket);

    // Then
    const int expected_count = 2;

    ASSERT_EQ(expected_count, particles.size());
}

void setupTwoParticlesThatShouldCombine_LabFrame(std::vector<Particle> &particles)
{
    // given
    particles.resize(2);

    const int start_position = 50;

    const int radius_0 = 10;
    const int radius_1 = 9;
    const int position_1 = start_position + radius_0 + radius_1 + 1; // edges 1 apart

    const int mass_0 = 10;
    const int mass_1 = 100;

    const Vector velocity_0 = {100.005, 100};
    const Vector velocity_1 = {99.9995, 100}; // total p = (100,100)

    particles[0].setMass(10);
    particles[0].setRadius(radius_0);
    particles[0].setPosition(start_position, start_position);
    particles[0].setVelocity(velocity_0);

    particles[1].setMass(100);
    particles[1].setRadius(radius_1);
    particles[1].setPosition(position_1, start_position);
    particles[1].setVelocity(velocity_1);
}

TEST_F(gravityCalculatorFixture, particleCombination_PositionConservingCOMGivenToParticle0_LabFrame)
{
    // Given
    setupTwoParticlesThatShouldCombine_LabFrame(particles);

    // When
    gravity_calculator.updateForcesAndHandleCombinations(particles, rocket);

    // Then
    const float expected_position = 68.18181818; // COM

    const float actual_particle_0_position = particles[0].getPosition()[0];

    ASSERT_EQ(expected_position, actual_particle_0_position);
}

TEST_F(gravityCalculatorFixture, particleCombination_VelocityConservingMomentumGivenToParticle0_LabFrame)
{
    // Given
    setupTwoParticlesThatShouldCombine_LabFrame(particles);

    // When
    gravity_calculator.updateForcesAndHandleCombinations(particles, rocket);

    // Then
    const Vector expected_velocity = {100, 100}; // NL3

    const Vector actual_particle_0_velocity = particles[0].getVelocity();

    ASSERT_EQ(expected_velocity, actual_particle_0_velocity);
}

TEST_F(gravityCalculatorFixture, particleCombination_forces_added)
{
    // Given
    setupTwoParticlesThatShouldCombine_LabFrame(particles);

    // When
    gravity_calculator.updateForcesAndHandleCombinations(particles, rocket);

    Force expected_force_0;
    expected_force_0.F = {2.5, 0}; // Newton said this
    expected_force_0.b = {50, 50};

    Force expected_force_1;
    expected_force_1.F = {-2.5, 0}; // Newton said this
    expected_force_1.b = {70, 50};
    std::vector<Force> expected_forces = {expected_force_0, expected_force_1};

    std::vector<Force> actual_forces = particles[0].getForces();

    EXPECT_EQ(expected_forces, actual_forces);
}

TEST_F(gravityCalculatorFixture, rocket_gravity_towards_particle_based_on_newton)
{
    // Given
    particles.resize(1);

    particles[0].setPosition(110, 100);
    particles[0].setMass(2);

    rocket.setPosition(100, 100);

    // When
    gravity_calculator.updateForcesAndHandleCombinations(particles, rocket);

    // Then
    Force expected_force;
    expected_force.F = {0.02, 0}; // Newton said this
    expected_force.b = {100, 100};

    std::vector<Force> expected_forces = {expected_force};

    std::vector<Force> actual_forces = rocket.getForces();

    EXPECT_EQ(expected_forces, actual_forces);
}

TEST_F(gravityCalculatorFixture, rocket_gravity_towards_two_particles_adds_up_based_on_newton)
{
    // Given
    particles.resize(2);

    particles[0].setPosition(110, 100);
    particles[0].setMass(2);

    particles[1].setPosition(100, 110);
    particles[1].setMass(2);

    rocket.setPosition(100, 100);

    // When
    gravity_calculator.updateForcesAndHandleCombinations(particles, rocket);

    // Then
    Force expected_force;
    expected_force.F = {0.02, 0.02}; // Newton said this
    expected_force.b = {100, 100};

    std::vector<Force> expected_forces = {expected_force};

    std::vector<Force> actual_forces = rocket.getForces();

    EXPECT_EQ(expected_forces, actual_forces);
}
