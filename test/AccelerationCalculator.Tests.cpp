#include "../src/calculators/AccelerationCalculator.h"

#include "../src/objects/RotationalParticle.h"
#include <vector>

#include <gtest/gtest.h>

class AccelerationCalculator_Fixture : public ::testing::Test
{
protected:
    AccelerationCalculator calculator;

    RotationalParticle rotating_particle;

    LinearParticle linear_particle;
};

TEST_F(AccelerationCalculator_Fixture, angular_no_forces_gets_no_acceleration)
{
    // Given
    // When
    calculator.calculateAngular(rotating_particle);

    // Then
    const float expected_acceleration_angular = 0;
    const float actual_acceleration_angular = rotating_particle.getAcceleration_Angular();

    ASSERT_EQ(expected_acceleration_angular, actual_acceleration_angular);
}

TEST_F(AccelerationCalculator_Fixture, angular_previous_accleration_and_no_forces_gets_no_acceleration)
{
    // Given
    rotating_particle.setAcceleration_Angular(100);

    // When
    calculator.calculateAngular(rotating_particle);

    // Then
    const float expected_acceleration_angular = 0;
    const float actual_acceleration_angular = rotating_particle.getAcceleration_Angular();

    ASSERT_EQ(expected_acceleration_angular, actual_acceleration_angular);
}

TEST_F(AccelerationCalculator_Fixture, angular_calculated_using_moments)
{
    // Given
    rotating_particle.setCom({100, 100});
    rotating_particle.setI(100);

    Force force;
    force.F = {0, 20};
    force.b = {99, 100};

    rotating_particle.addForce(force);

    // When
    calculator.calculateAngular(rotating_particle);

    // Then
    const float expected_acceleration_angular = -0.2;
    const float actual_acceleration_angular = rotating_particle.getAcceleration_Angular();

    ASSERT_EQ(expected_acceleration_angular, actual_acceleration_angular);
}

TEST_F(AccelerationCalculator_Fixture, angular_parrallel_makes_no_acceleration)
{
    // Given
    const Vector com = {100, 50};

    rotating_particle.setCom(com);
    rotating_particle.setI(100);

    const Vector direction = {25, 13};

    Force force;
    force.F = 4 * direction;
    force.b = com + 3 * direction;

    rotating_particle.addForce(force);

    // When
    calculator.calculateAngular(rotating_particle);

    // Then
    const float expected_acceleration_angular = 0;
    const float actual_acceleration_angular = rotating_particle.getAcceleration_Angular();

    ASSERT_NEAR(expected_acceleration_angular, actual_acceleration_angular, (float)(1)/1000);
}

TEST_F(AccelerationCalculator_Fixture, angular_calculated_using_moments_more_forces)
{
    // Given
    rotating_particle.setCom({100, 100});
    rotating_particle.setI(100);

    Force force;
    force.F = {0, 20};
    force.b = {99, 100};

    rotating_particle.addForce(force);
    rotating_particle.addForce(force);

    // When
    calculator.calculateAngular(rotating_particle);

    // Then
    const float expected_acceleration_angular = -0.4;
    const float actual_acceleration_angular = rotating_particle.getAcceleration_Angular();

    ASSERT_EQ(expected_acceleration_angular, actual_acceleration_angular);
}

TEST_F(AccelerationCalculator_Fixture, add_acceleration_based_on_force)
{
    // Given
    linear_particle.setMass(10);

    Force force;
    force.F = {10, 20};
    force.b = {99, 100};

    linear_particle.addForce(force);
    linear_particle.addForce(force);

    // When
    calculator.calculateLinear(linear_particle);

    // Then
    const Vector expected_acceleration = {2, 4};
    const Vector actual_acceleration = linear_particle.getAcceleration();

    ASSERT_EQ(expected_acceleration, actual_acceleration);
}
