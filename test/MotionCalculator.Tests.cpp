#include "../src/calculators/MotionCalculator.h"

#include "../src/objects/RotationalParticle.h"

#include <gtest/gtest.h>

class MotionCalculator_Fixture : public ::testing::Test
{
protected:
    MotionCalculator calculator;

    RotationalParticle rotating_particle;

    LinearParticle linear_particle;
};

TEST_F(MotionCalculator_Fixture, angle)
{
    // Given
    const float dt = 10;

    rotating_particle.setAngle(1);
    rotating_particle.setVelocity_Angular(2);
    rotating_particle.setAcceleration_Angular(0.2);

    // When
    calculator.calculateAngular(rotating_particle, dt);

    // Then
    const float expected_angle = 31;
    const float actual_angle = rotating_particle.getAngle();

    ASSERT_EQ(expected_angle, actual_angle);
}

TEST_F(MotionCalculator_Fixture, angular_velocity)
{
    // Given
    const float dt = 10;

    rotating_particle.setAcceleration_Angular(5);

    // When
    calculator.calculateAngular(rotating_particle, dt);

    // Then
    const float expected_angular_velocity = 50;
    const float actual_angular_velocity = rotating_particle.getVelocity_Angular();

    ASSERT_EQ(expected_angular_velocity, actual_angular_velocity);
}

TEST_F(MotionCalculator_Fixture, position)
{
    // Given
    const float dt = 10;

    linear_particle.setPosition({5, 10});
    linear_particle.setVelocity({6, 11});
    linear_particle.setAcceleration({0.2, 0.1});

    // When
    calculator.calculateLinear(linear_particle, dt);

    // Then
    const Vector expected_position = {75, 125};
    const Vector actual_position = linear_particle.getPosition();

    ASSERT_EQ(expected_position, actual_position);
}

TEST_F(MotionCalculator_Fixture, velocity)
{
    // Given
    const float dt = 10;

    linear_particle.setVelocity({6, 11});
    linear_particle.setAcceleration({1, 2});

    // When
    calculator.calculateLinear(linear_particle, dt);

    // Then
    const Vector expected_velocity = {16, 31};
    const Vector actual_velocity = linear_particle.getVelocity();

    ASSERT_EQ(expected_velocity, actual_velocity);
}
