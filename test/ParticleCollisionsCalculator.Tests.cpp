#include <gtest/gtest.h>

#include "../src/calculators/ParticleCollisionsCalculator.h"
#include <math.h>

Vector getTotalMomentum(const std::vector<Particle> &particles)
{
    Vector p = {0, 0};

    for (const Particle &particle : particles)
    {
        p += particle.getMass() * particle.getVelocity();
    }

    return p;
}

float getTotalKE(const std::vector<Particle> &particles)
{
    float KE = 0;

    for (const Particle &particle : particles)
    {
        const float speed = particle.getVelocity().getMagnitude();
        KE += 0.5 * particle.getMass() * speed * speed;
    }

    return KE;
}

TEST(particle_collisions, direct_hit_stationary)
{
    // setup
    std::vector<Particle> particles;
    particles.resize(2);

    // given
    particles[0].setRadius(10);
    particles[0].setPosition(100, 100);
    particles[0].setVelocity(10, 0);

    particles[1].setRadius(10);
    particles[1].setPosition(115, 100); // overlap of 5
    particles[1].setVelocity(0, 0);

    ParticleCollisionsCalculator particle_collisions_calculator;

    // when
    particle_collisions_calculator.updateParticles(particles);

    // then - positions
    const Vector actual_particle_zero_position = particles[0].getPosition();
    const Vector expected_particle_zero_position = {97.5, 100.0};

    EXPECT_EQ(expected_particle_zero_position, actual_particle_zero_position);

    const Vector actual_particle_one_position = particles[1].getPosition();
    const Vector expected_particle_one_position = {117.5, 100.0};

    EXPECT_EQ(expected_particle_one_position, actual_particle_one_position);

    // then - velocities
    const Vector actual_particle_zero_velocity = particles[0].getVelocity();
    const Vector expected_particle_zero_velocity = {0, 0};

    EXPECT_EQ(expected_particle_zero_velocity, actual_particle_zero_velocity);

    const Vector actual_particle_one_velocity = particles[1].getVelocity();
    const Vector expected_particle_one_velocity = {10, 0};

    EXPECT_EQ(expected_particle_one_velocity, actual_particle_one_velocity);
}

TEST(particle_collisions, direct_hit_both_moving)
{
    // setup
    std::vector<Particle> particles;
    particles.resize(2);

    // given
    particles[0].setRadius(10);
    particles[0].setPosition(100, 100);
    particles[0].setVelocity(10, 0);

    particles[1].setRadius(10);
    particles[1].setPosition(115, 100); // overlap of 5
    particles[1].setVelocity(-10, 0);

    ParticleCollisionsCalculator particle_collisions_calculator;
    // when
    particle_collisions_calculator.updateParticles(particles);

    // then - positions
    const Vector actual_particle_zero_position = particles[0].getPosition();
    const Vector expected_particle_zero_position = {97.5, 100.0};

    EXPECT_EQ(expected_particle_zero_position, actual_particle_zero_position);

    const Vector actual_particle_one_position = particles[1].getPosition();
    const Vector expected_particle_one_position = {117.5, 100.0};

    EXPECT_EQ(expected_particle_one_position, actual_particle_one_position);

    // then - velocities
    const Vector actual_particle_zero_velocity = particles[0].getVelocity();
    const Vector expected_particle_zero_velocity = {-10, 0};

    EXPECT_EQ(expected_particle_zero_velocity, actual_particle_zero_velocity);

    const Vector actual_particle_one_velocity = particles[1].getVelocity();
    const Vector expected_particle_one_velocity = {10, 0};

    EXPECT_EQ(expected_particle_one_velocity, actual_particle_one_velocity);
}

TEST(particle_collisions, direct_hit_both_moving_same_direction)
{
    // setup
    std::vector<Particle> particles;
    particles.resize(2);

    // given
    particles[0].setRadius(10);
    particles[0].setPosition(100, 100);
    particles[0].setVelocity(10, 0);

    particles[1].setRadius(10);
    particles[1].setPosition(115, 100); // overlap of 5
    particles[1].setVelocity(5, 0);

    ParticleCollisionsCalculator particle_collisions_calculator;
    // when
    particle_collisions_calculator.updateParticles(particles);

    // then - positions
    const Vector actual_particle_zero_position = particles[0].getPosition();
    const Vector expected_particle_zero_position = {97.5, 100.0};

    EXPECT_EQ(expected_particle_zero_position, actual_particle_zero_position);

    const Vector actual_particle_one_position = particles[1].getPosition();
    const Vector expected_particle_one_position = {117.5, 100.0};

    EXPECT_EQ(expected_particle_one_position, actual_particle_one_position);

    // then - velocities
    const Vector actual_particle_zero_velocity = particles[0].getVelocity();
    const Vector expected_particle_zero_velocity = {5, 0};

    EXPECT_EQ(expected_particle_zero_velocity, actual_particle_zero_velocity);

    const Vector actual_particle_one_velocity = particles[1].getVelocity();
    const Vector expected_particle_one_velocity = {10, 0};

    EXPECT_EQ(expected_particle_one_velocity, actual_particle_one_velocity);
}

TEST(particle_collisions, direct_hit_big_mass_moving)
{
    // setup
    std::vector<Particle> particles;
    particles.resize(2);

    // given
    particles[0].setRadius(100);
    particles[0].setMass(100);
    particles[0].setPosition(200, 200);
    particles[0].setVelocity(10, 0);

    particles[1].setRadius(4);
    particles[1].setMass(1);
    particles[1].setPosition(98, 200); // overlap of 2
    particles[1].setVelocity(0, 0);

    const Vector p_before = getTotalMomentum(particles);
    const float ke_before = getTotalKE(particles);

    ParticleCollisionsCalculator particle_collisions_calculator;
    // when
    particle_collisions_calculator.updateParticles(particles);

    // then - positions
    const Vector actual_particle_zero_position = particles[0].getPosition();
    const Vector expected_particle_zero_position = {200.00012, 200.0};

    EXPECT_EQ(expected_particle_zero_position, actual_particle_zero_position);

    const Vector actual_particle_one_position = particles[1].getPosition();
    const Vector expected_particle_one_position = {96.00013, 200.0};

    EXPECT_EQ(expected_particle_one_position, actual_particle_one_position);

    // then - velocities
    const Vector actual_particle_zero_velocity = particles[0].getVelocity();
    const Vector expected_particle_zero_velocity = {9.80198, 0};

    EXPECT_EQ(expected_particle_zero_velocity, actual_particle_zero_velocity);

    const Vector actual_particle_one_velocity = particles[1].getVelocity();
    const Vector expected_particle_one_velocity = {19.802, 0};

    EXPECT_EQ(expected_particle_one_velocity, actual_particle_one_velocity);

    // and total momentum is conserved
    const Vector p_after = getTotalMomentum(particles);

    EXPECT_EQ(p_before, p_after);

    // and total k.e conserved
    const float ke_after = getTotalKE(particles);
    EXPECT_FLOAT_EQ(ke_before, ke_after);
}

TEST(particle_collisions, direct_hit_small_mass_moving)
{
    // setup
    std::vector<Particle> particles;
    particles.resize(2);

    // given
    particles[0].setRadius(100);
    particles[0].setMass(100);
    particles[0].setPosition(200, 200);
    particles[0].setVelocity(0, 0);

    particles[1].setRadius(4);
    particles[1].setMass(1);
    particles[1].setPosition(98, 200); // overlap of 2
    particles[1].setVelocity(100, 0);

    const Vector p_before = getTotalMomentum(particles);
    const float ke_before = getTotalKE(particles);

    ParticleCollisionsCalculator particle_collisions_calculator;

    // when
    particle_collisions_calculator.updateParticles(particles);

    // then - positions
    const Vector actual_particle_zero_position = particles[0].getPosition();
    const Vector expected_particle_zero_position = {200.00012, 200.0};

    EXPECT_EQ(expected_particle_zero_position, actual_particle_zero_position);

    const Vector actual_particle_one_position = particles[1].getPosition();
    const Vector expected_particle_one_position = {96.00013, 200.0};

    EXPECT_EQ(expected_particle_one_position, actual_particle_one_position);

    // then - velocities
    const Vector actual_particle_zero_velocity = particles[0].getVelocity();
    const Vector expected_particle_zero_velocity = {1.9802, 0};

    EXPECT_EQ(expected_particle_zero_velocity, actual_particle_zero_velocity);

    const Vector actual_particle_one_velocity = particles[1].getVelocity();
    const Vector expected_particle_one_velocity = {-98.0198, 0};

    EXPECT_EQ(expected_particle_one_velocity, actual_particle_one_velocity);

    // and total momentum is conserved
    const Vector p_after = getTotalMomentum(particles);

    EXPECT_EQ(p_before, p_after);

    // and total k.e conserved
    const float ke_after = getTotalKE(particles);
    EXPECT_FLOAT_EQ(ke_before, ke_after);
}

TEST(particle_collisions, indirect_hit_momentum_conserved)
{
    // setup
    std::vector<Particle> particles;
    particles.resize(2);

    // given
    particles[0].setRadius(10);
    particles[0].setPosition(200, 200);
    particles[0].setVelocity(10, -5);

    particles[1].setRadius(10);
    particles[1].setPosition(185, 181); // x overlap 5, y overlap 1
    particles[1].setVelocity(100, 0);

    const Vector p_before = getTotalMomentum(particles);
    const float KE_before = getTotalKE(particles);

    ParticleCollisionsCalculator particle_collisions_calculator;
    // when
    particle_collisions_calculator.updateParticles(particles);

    // then total momentum is conserved
    const Vector p_after = getTotalMomentum(particles);
    EXPECT_EQ(p_before, p_after);

    // and energy conserved
    const float KE_after = getTotalKE(particles);
    EXPECT_EQ(KE_before, KE_after);
}