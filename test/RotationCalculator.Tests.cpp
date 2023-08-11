#include "../src/calculators/RotationCalculator.h"

#include <gtest/gtest.h>

TEST(Rotation_Calculator, particle_at_center_gets_v_and_a_rotated)
{
    // given
    RotationCalculator rotation_calculator;

    LinearParticle particle;

    const Vector center_of_rotation = {100, 100};

    particle.setPosition(center_of_rotation);
    particle.setVelocity(10, 10);
    particle.setAcceleration(1, 1);

    const float angle = PI;

    // when
    rotation_calculator.rotateParticleAboutPoint(center_of_rotation, angle, particle);

    // then
    LinearParticle expected_particle;
    expected_particle.setPosition(center_of_rotation);
    expected_particle.setVelocity(-10, -10);
    expected_particle.setAcceleration(-1, -1);

    ASSERT_EQ(expected_particle, particle);
}

TEST(Rotation_Calculator, particle_center_at_origin_gets_rotated)
{
    // given
    RotationCalculator rotation_calculator;

    LinearParticle particle;

    const Vector center_of_rotation = {0, 0};

    particle.setPosition(100, 100);
    particle.setVelocity(10, 10);
    particle.setAcceleration(1, 1);

    const float angle = PI;

    // when
    rotation_calculator.rotateParticleAboutPoint(center_of_rotation, angle, particle);

    // then
    LinearParticle expected_particle;
    expected_particle.setPosition(-100, -100);
    expected_particle.setVelocity(-10, -10);
    expected_particle.setAcceleration(-1, -1);

    ASSERT_EQ(expected_particle, particle);
}

TEST(Rotation_Calculator, particle_at_center_gets_v_and_a_rotated_trig)
{
    // given
    RotationCalculator rotation_calculator;

    LinearParticle particle;

    const Vector center_of_rotation = {100, 100};

    particle.setPosition(center_of_rotation);
    particle.setVelocity(10, 10);
    particle.setAcceleration(1, 1);

    const float cos_angle = -1;
    const float sin_angle = 0;

    // when
    rotation_calculator.rotateParticleAboutPoint(center_of_rotation, cos_angle, sin_angle, particle);

    // then
    LinearParticle expected_particle;
    expected_particle.setPosition(center_of_rotation);
    expected_particle.setVelocity(-10, -10);
    expected_particle.setAcceleration(-1, -1);

    ASSERT_EQ(expected_particle, particle);
}

TEST(Rotation_Calculator, particle_center_at_origin_gets_rotated_trig)
{
    // given
    RotationCalculator rotation_calculator;

    LinearParticle particle;

    const Vector center_of_rotation = {0, 0};

    particle.setPosition(100, 100);
    particle.setVelocity(10, 10);
    particle.setAcceleration(1, 1);

    const float cos_angle = -1;
    const float sin_angle = 0;

    // when
    rotation_calculator.rotateParticleAboutPoint(center_of_rotation, cos_angle, sin_angle, particle);

    // then
    LinearParticle expected_particle;
    expected_particle.setPosition(-100, -100);
    expected_particle.setVelocity(-10, -10);
    expected_particle.setAcceleration(-1, -1);

    ASSERT_EQ(expected_particle, particle);
}

TEST(Rotation_Calculator, dot_at_center_no_change)
{
    // given
    RotationCalculator rotation_calculator;

    Dot dot;

    const Vector center_of_rotation = {100, 100};

    dot.setPosition(center_of_rotation);

    const float angle = 180;

    // when
    rotation_calculator.rotateParticleAboutPoint(center_of_rotation, angle, dot);

    // then
    const Vector expected_position = {100, 100};

    ASSERT_EQ(expected_position, dot.getPosition());
}

TEST(Rotation_Calculator, dot_center_at_origin_gets_rotated)
{
    // given
    RotationCalculator rotation_calculator;

    Dot dot;

    const Vector center_of_rotation = {0, 0};

    dot.setPosition(Vector{100, 100});

    const float angle = PI;

    // when
    rotation_calculator.rotateParticleAboutPoint(center_of_rotation, angle, dot);

    // then
    const Vector expected_position = {-100, -100};

    ASSERT_EQ(expected_position, dot.getPosition());
}

TEST(Rotation_Calculator, dot_at_center_no_change_trig)
{
    // given
    RotationCalculator rotation_calculator;

    Dot dot;

    const Vector center_of_rotation = {100, 100};

    dot.setPosition(center_of_rotation);

    const float cos_angle = -1;
    const float sin_angle = 0;

    // when
    rotation_calculator.rotateParticleAboutPoint(center_of_rotation, cos_angle, sin_angle, dot);

    // then
    const Vector expected_position = {100, 100};

    ASSERT_EQ(expected_position, dot.getPosition());
}

TEST(Rotation_Calculator, dot_center_at_origin_gets_rotated_trig)
{
    // given
    RotationCalculator rotation_calculator;

    Dot dot;

    const Vector center_of_rotation = {0, 0};

    dot.setPosition(Vector{100, 100});

    const float cos_angle = -1;
    const float sin_angle = 0;

    // when
    rotation_calculator.rotateParticleAboutPoint(center_of_rotation, cos_angle, sin_angle, dot);

    // then
    const Vector expected_position = {-100, -100};

    ASSERT_EQ(expected_position, dot.getPosition());
}

TEST(Rotation_Calculator, rotation_particle_at_center_gets_v_and_a_rotated)
{
    // given
    RotationCalculator rotation_calculator;

    RotationalParticle particle;

    const Vector center_of_rotation = {100, 100};

    particle.setPosition(center_of_rotation);
    particle.setVelocity(10, 10);
    particle.setAcceleration(1, 1);

    particle.setAngle(PI / 2);

    const float angle = PI;

    // when
    rotation_calculator.rotateParticleAboutPoint(center_of_rotation, angle, particle);

    // then
    RotationalParticle expected_particle;
    expected_particle.setPosition(center_of_rotation);
    expected_particle.setVelocity(-10, -10);
    expected_particle.setAcceleration(-1, -1);

    expected_particle.setAngle(3 * PI / 2);

    ASSERT_EQ(expected_particle, particle);
}

TEST(Rotation_Calculator, rotation_particle_center_at_origin_gets_rotated)
{
    // given
    RotationCalculator rotation_calculator;

    RotationalParticle particle;

    const Vector center_of_rotation = {0, 0};

    particle.setPosition(100, 100);
    particle.setVelocity(10, 10);
    particle.setAcceleration(1, 1);

    particle.setAngle(PI / 2);

    const float angle = PI;

    // when
    rotation_calculator.rotateParticleAboutPoint(center_of_rotation, angle, particle);

    // then
    RotationalParticle expected_particle;
    expected_particle.setPosition(-100, -100);
    expected_particle.setVelocity(-10, -10);
    expected_particle.setAcceleration(-1, -1);

    expected_particle.setAngle(3 * PI / 2);

    ASSERT_EQ(expected_particle, particle);
}
