#include <gtest/gtest.h>

#include "../src/objects/RotationalParticle.h"

TEST(RotationalParticle, com_default)
{
    // Given
    RotationalParticle rotational_particle;

    // When
    const Vector com = rotational_particle.getCom();

    // Then
    const Vector zero_vector = {0, 0};
    ASSERT_EQ(zero_vector, com);
}

TEST(RotationalParticle, set_com)
{
    // Given
    RotationalParticle rotational_particle;

    const Vector input_com = {101, 39};

    // When
    rotational_particle.setCom(input_com);

    // Then
    const Vector com = rotational_particle.getCom();
    ASSERT_EQ(input_com, com);
}

TEST(RotationalParticle, angle_deafults_0)
{
    // Given
    RotationalParticle rotational_particle;

    // When
    const float angle = rotational_particle.getAngle();

    // Then
    ASSERT_EQ(0, angle);
}

TEST(RotationalParticle, set_angle)
{
    // Given
    RotationalParticle rotational_particle;
    const float input_angle = PI;

    // When
    rotational_particle.setAngle(input_angle);

    // Then
    const float angle = rotational_particle.getAngle();

    ASSERT_EQ(input_angle, angle);
}

TEST(RotationalParticle, velocity_angular_deafults_0)
{
    // Given
    RotationalParticle rotational_particle;

    // When
    const float velocity_angular = rotational_particle.getVelocity_Angular();

    // Then
    ASSERT_EQ(0, velocity_angular);
}

TEST(RotationalParticle, set_velocity_angular)
{
    // Given
    RotationalParticle rotational_particle;
    const float input_velocity_angular = PI + 1;

    // When
    rotational_particle.setVelocity_Angular(input_velocity_angular);

    // Then
    const float velocity_angular = rotational_particle.getVelocity_Angular();

    ASSERT_EQ(input_velocity_angular, velocity_angular);
}

TEST(RotationalParticle, acceleration_angular_deafults_0)
{
    // Given
    RotationalParticle rotational_particle;

    // When
    const float acceleration_angular = rotational_particle.getAcceleration_Angular();

    // Then
    ASSERT_EQ(0, acceleration_angular);
}

TEST(RotationalParticle, set_acceleration_angular)
{
    // Given
    RotationalParticle rotational_particle;
    const float input_acceleration_angular = PI + 2;

    // When
    rotational_particle.setAcceleration_Angular(input_acceleration_angular);

    // Then
    const float acceleration_angular = rotational_particle.getAcceleration_Angular();

    ASSERT_EQ(input_acceleration_angular, acceleration_angular);
}

TEST(RotationalParticle, I_defaults_1)
{
    // Given
    RotationalParticle rotational_particle;

    // When
    const float I = rotational_particle.getI();

    // Then
    ASSERT_EQ(10000, I);
}

TEST(RotationalParticle, set_I)
{
    // Given
    RotationalParticle rotational_particle;
    const float input_I = 36.5698;

    // When
    rotational_particle.setI(input_I);

    // Then
    const float I = rotational_particle.getI();

    ASSERT_EQ(input_I, I);
}

TEST(RotationalParticle, getDirectionVector_default_x_direction)
{
    // Given
    RotationalParticle rotational_particle;

    // When
    const Vector actaul_direction_vector = rotational_particle.getDirectionVector();

    // Then
    const Vector expected_direction_vector = {1, 0};

    ASSERT_EQ(expected_direction_vector, actaul_direction_vector);
}

TEST(RotationalParticle, getDirectionVector_right_angle)
{
    // Given
    RotationalParticle rotational_particle;
    rotational_particle.setAngle(PI / 2);

    // When
    const Vector actaul_direction_vector = rotational_particle.getDirectionVector();

    // Then
    const Vector expected_direction_vector = {0, 1};

    ASSERT_EQ(expected_direction_vector, actaul_direction_vector);
}

TEST(RotationalParticle, getDirectionVector_45_degrees)
{
    // Given
    RotationalParticle rotational_particle;
    rotational_particle.setAngle(PI / 4);

    // When
    const Vector actaul_direction_vector = rotational_particle.getDirectionVector();

    // Then
    const Vector expected_direction_vector = {(float)sqrt(2) / 2, (float)sqrt(2) / 2};

    ASSERT_EQ(expected_direction_vector, actaul_direction_vector);
}
