#include <gtest/gtest.h>

#include "../src/objects/LinearParticle.h"
#include "../src/Force.h"

TEST(linear_particle, default_position)
{
    // given
    LinearParticle linear_particle;

    // when
    const Vector actual_position = linear_particle.getPosition();

    // then
    const Vector expected_position = {0, 0};

    ASSERT_EQ(expected_position, actual_position);
}

TEST(linear_particle, setPosition)
{
    // given
    LinearParticle linear_particle;
    const Vector input_position = {2.5, -3.9};

    // when
    linear_particle.setPosition(input_position);

    // then
    const Vector actual_position = linear_particle.getPosition();

    ASSERT_EQ(input_position, actual_position);
}

TEST(linear_particle, default_velocity)
{
    // given
    LinearParticle linear_particle;

    // when
    Vector actual_velocity = linear_particle.getVelocity();

    // then
    const Vector expected_velocity = {0, 0};

    ASSERT_EQ(expected_velocity, actual_velocity);
}

TEST(linear_particle, setVelocity)
{
    // given
    LinearParticle linear_particle;
    Vector input_velocity = {15.3, -39.9};

    // when
    linear_particle.setVelocity(input_velocity);

    // then
    const Vector actual_velocity = linear_particle.getVelocity();

    ASSERT_EQ(input_velocity, actual_velocity);
}

TEST(linear_particle, default_acceleration)
{
    // given
    LinearParticle linear_particle;

    // when
    Vector actual_acceleration = linear_particle.getAcceleration();

    // then
    const Vector expected_acceleration = {0, 0};

    ASSERT_EQ(expected_acceleration, actual_acceleration);
}

TEST(linear_particle, setAcceleration)
{
    // given
    LinearParticle linear_particle;
    Vector input_acceleration = {15.3, -39.9};

    // when
    linear_particle.setAcceleration(input_acceleration);

    // then
    const Vector actual_acceleration = linear_particle.getAcceleration();

    ASSERT_EQ(input_acceleration, actual_acceleration);
}

TEST(linear_particle, display_position_default)
{
    // given
    LinearParticle linear_particle;

    // when
    Vector actual_display_position = linear_particle.getDisplayPosition();

    // then
    const Vector expected_display_position = {0, 0};

    ASSERT_EQ(expected_display_position, actual_display_position);
}

TEST(linear_particle, set_display_position)
{
    // given
    LinearParticle linear_particle;
    Vector input_display_position = {15.3, -39.9};

    // when
    linear_particle.setDisplayPosition(input_display_position);

    // then
    const Vector actual_display_position = linear_particle.getDisplayPosition();

    ASSERT_EQ(input_display_position, actual_display_position);
}

TEST(linear_particle, time_since_last_updated_zero_at_start)
{
    // given
    LinearParticle exampleParticle;
    const float current_time = 100; // random number

    // when
    const float actual_intial_time_since_updated = exampleParticle.getTimeSinceLastUpdated(current_time);

    // then
    const float expected_intial_time_since_updated = 0;

    EXPECT_EQ(actual_intial_time_since_updated, expected_intial_time_since_updated);
}

TEST(linear_particle, time_since_last_updated_after_update)
{
    // given
    LinearParticle exampleParticle;
    const float start_time = 100;
    const float time_now = 105;

    // when
    exampleParticle.setTimeLastUpdated(start_time);
    const float actual_time_since_updated = exampleParticle.getTimeSinceLastUpdated(time_now);

    // then
    const float expected_time_since_updated = 5;

    EXPECT_EQ(actual_time_since_updated, expected_time_since_updated);
}

TEST(linear_particle, getTimeLastUpdated)
{
    // given
    LinearParticle exampleParticle;
    const float time = 100;

    // when
    exampleParticle.setTimeLastUpdated(time);
    const float actual_time_updated = exampleParticle.getTimeLastUpdated();

    // then
    const float expected_time_updated = time;

    EXPECT_EQ(expected_time_updated, actual_time_updated);
}

TEST(linear_particle, getMass_return_zero_if_radius_not_set)
{
    // given
    LinearParticle exampleParticle;

    // when
    const float actual_default_mass = exampleParticle.getMass();

    // then
    const float expected_default_mass = 1;
    EXPECT_EQ(expected_default_mass, actual_default_mass);
}

TEST(linear_particle, getMass_returns_mass_if_set)
{
    // given
    LinearParticle exampleParticle;
    exampleParticle.setMass(8);

    // when
    const float actual_mass = exampleParticle.getMass();

    // then
    const float expected_mass = 8;
    EXPECT_EQ(expected_mass, actual_mass);
}

TEST(linear_particle, boolean_same)
{
    // given
    LinearParticle exampleParticle_0;
    LinearParticle exampleParticle_1;

    // then
    ASSERT_EQ(exampleParticle_0, exampleParticle_1);
}

TEST(linear_particle, boolean_different)
{
    // given
    LinearParticle exampleParticle_0;
    LinearParticle exampleParticle_1;

    exampleParticle_0.setPosition(100, 100);

    // when
    const bool are_equal = exampleParticle_0 == exampleParticle_1;

    // then
    ASSERT_FALSE(are_equal);
}

TEST(linear_particle, get_forces)
{
    // given
    LinearParticle linear_particle;

    // when
    std::vector<Force> forces = linear_particle.getForces();

    // then
    std::vector<Force> empty_vector = {};

    ASSERT_EQ(empty_vector, forces);
}

TEST(linear_particle, add_force)
{
    // given
    LinearParticle linear_particle;

    const Vector F = {10, 5};
    const Vector b = {100, 50};

    Force force;
    force.F = F;
    force.b = b;

    // when
    linear_particle.addForce(force);

    // then
    std::vector<Force> forces = linear_particle.getForces();
    std::vector<Force> expected_forces_vector = {force};

    ASSERT_EQ(expected_forces_vector, forces);
}

TEST(linear_particle, reset_forces)
{
    // given
    LinearParticle linear_particle;

    const Vector F = {10, 5};
    const Vector b = {100, 50};

    Force force;
    force.F = F;
    force.b = b;

    linear_particle.addForce(force);
    linear_particle.addForce(force);
    linear_particle.addForce(force);

    // when
    linear_particle.resetForces();

    // then
    std::vector<Force> forces = linear_particle.getForces();
    std::vector<Force> empty_vector = {};

    ASSERT_EQ(empty_vector, forces);
}
