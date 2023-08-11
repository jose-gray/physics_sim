#include <gtest/gtest.h>

#include "../src/objects/Particle.h"

TEST(particle, getRadius_returns_1_if_not_set)
{
    // given
    Particle particle;

    // when
    int actual_default_radius = particle.getRadius();

    // then
    int expected_default_radius = 1;
    EXPECT_EQ(actual_default_radius, expected_default_radius);
}

TEST(particle, setRadius_returns_radius_if_set_and_mass_correct)
{
    // given
    Particle particle;

    // when
    particle.setRadius(5);
    int actual_radius = particle.getRadius();

    // then
    int expected_radius = 5;
    EXPECT_EQ(actual_radius, expected_radius);
}

TEST(particle, getDisplayRadius_returns_1_if_not_set)
{
    // given
    Particle particle;

    // when
    int actual_default_display_radius = particle.getDisplayRadius();

    // then
    int expected_default_display_radius = 1;
    EXPECT_EQ(actual_default_display_radius, expected_default_display_radius);
}

TEST(particle, setDisplayRadius_returns_radius_if_set_and_mass_correct)
{
    // given
    Particle particle;

    // when
    particle.setDisplayRadius(5);
    int actual_display_radius = particle.getDisplayRadius();

    // then
    int expected_display_radius = 5;
    EXPECT_EQ(actual_display_radius, expected_display_radius);
}

TEST(particle, getRestitution_returns_1_if_not_set)
{
    // given
    Particle particle;

    // when
    const float actual_default_restitution = particle.getRestitution();

    // then
    const float expected_default_restitution = 1;
    EXPECT_EQ(actual_default_restitution, expected_default_restitution);
}

TEST(particle, setRestitution_returns_restitution_if_set)
{
    // given
    Particle particle;

    // when
    particle.setRestitution(0.5);
    const float actual_default_restitution = particle.getRestitution();

    // then
    const float expected_default_restitution = 0.5;
    EXPECT_EQ(actual_default_restitution, expected_default_restitution);
}

TEST(particle, getCharge_returns_charge_zero_if_not_set)
{
    // given
    Particle particle;

    // when
    const float actual_charge = particle.getCharge();

    // then
    const float expected_charge = 0;
    EXPECT_EQ(expected_charge, actual_charge);
}

TEST(particle, getCharge_returns_charge_if_set)
{
    // given
    Particle particle;
    particle.setCharge(1);

    // when
    const float actual_charge = particle.getCharge();

    // then
    const float expected_charge = 1;
    EXPECT_EQ(expected_charge, actual_charge);
}

TEST(particle, getFixed_return_false_if_not_set)
{
    // given
    Particle particle;

    // when
    const float actual_is_fixed = particle.getIsFixed();

    // then
    const float expected_is_fixed = false;
    EXPECT_EQ(expected_is_fixed, actual_is_fixed);
}

TEST(particle, getFixed_return_true_if_set)
{
    // given
    Particle particle;

    // when
    particle.fixParticle();

    const float actual_is_fixed = particle.getIsFixed();

    // then
    const float expected_is_fixed = true;
    EXPECT_EQ(expected_is_fixed, actual_is_fixed);
}

TEST(particle, particle_bool_false_base_same)
{
    // given
    Particle particle_one;
    particle_one.setPosition(100, 100);
    particle_one.setRadius(100);

    Particle particle_two;
    particle_two.setPosition(100, 100);
    particle_two.setRadius(99);

    // when
    bool are_same = particle_one == particle_two;

    // then
    ASSERT_FALSE(are_same);
}

TEST(particle, particle_bool_false_base_different)
{
    // given
    Particle particle_one;
    particle_one.setPosition(100, 100);
    particle_one.setRadius(100);

    Particle particle_two;
    particle_two.setPosition(99, 95);
    particle_two.setRadius(100);

    // when
    bool are_same = particle_one == particle_two;

    // then
    ASSERT_FALSE(are_same);
}

TEST(particle, particle_bool_true)
{
    // given
    Particle particle_one;
    particle_one.setPosition(100, 100);
    particle_one.setRadius(100);

    Particle particle_two;
    particle_two.setPosition(100, 100);
    particle_two.setRadius(100);

    // when
    bool are_same = particle_one == particle_two;

    // then
    ASSERT_TRUE(are_same);
}

TEST(particle, copy_using_equals)
{
    // given
    Particle particle_one;
    particle_one.setPosition(101, 101);
    particle_one.setVelocity(102, 102);
    particle_one.setAcceleration(103, 103);
    particle_one.setMass(104);
    particle_one.setTimeLastUpdated(105);
    particle_one.setRadius(106);
    particle_one.setRestitution(107);
    particle_one.setCharge(108);
    particle_one.setColor(GREEN);

    Force force;
    force.F = {10, 2};
    force.b = {5, 3};
    particle_one.addForce(force);

    Particle particle_two;

    // when
    particle_two = particle_one;

    // then
    ASSERT_EQ(particle_one, particle_two);
}
