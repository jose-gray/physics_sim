#include <gtest/gtest.h>

#include "../src/calculators/WallCalculator.h"

TEST(WallCalculator, update_moves_wall_constant_velocity)
{
    // setup
    Wall wall;
    WallCalculator wall_calculator;

    // given
    wall.setTimeLastUpdated(0);
    wall.setVelocity(10);

    const int time = 1;

    // when
    wall_calculator.updateWall(wall, time);

    // then
    const float actual_position = wall.getPosition();
    const float expected_position = 10;

    ASSERT_EQ(expected_position, actual_position);
}

TEST(WallCalculator, update_twice_moves_wall_constant_velocity)
{
    // setup
    Wall wall;
    WallCalculator wall_calculator;

    // given
    wall.setTimeLastUpdated(0);
    wall.setVelocity(10);

    // when
    int time = 1;
    wall_calculator.updateWall(wall, time);

    time = 3;
    wall_calculator.updateWall(wall, time);

    // then
    const float actual_position = wall.getPosition();
    const float expected_position = 30;

    ASSERT_EQ(expected_position, actual_position);
}

TEST(WallCalculator, Oscilations_updates_position_and_velocity_correctly)
{
    // setup
    Wall wall;
    const direction orientation = y;
    const wallLimitType limit_type = max;
    const float position = 15;
    const int length = 250;
    wall.setupWall(orientation, limit_type, position, length);

    float actual_position;
    float expected_position;
    float actual_velocity;
    float expected_velocity;
    float time;

    // given
    const int equilibrium_position = 50;
    const int amplitude = 10;
    const float time_period = 1;
    wall.setOscillation(equilibrium_position, amplitude, time_period);

    WallCalculator wall_calculator;

    // when
    time = 0;
    wall_calculator.updateWall(wall, time);

    // then
    actual_position = wall.getPosition();
    expected_position = 60;

    ASSERT_EQ(expected_position, actual_position);

    expected_velocity = 0;
    actual_velocity = wall.getVelocity();

    ASSERT_NEAR(expected_velocity, actual_velocity, 0.001);

    // when
    time = 0.25;
    wall_calculator.updateWall(wall, time);

    // then
    actual_position = wall.getPosition();
    expected_position = 50;

    ASSERT_EQ(expected_position, actual_position);

    expected_velocity = -62.831856;
    actual_velocity = wall.getVelocity();

    ASSERT_FLOAT_EQ(expected_velocity, actual_velocity);

    // when
    time = 0.5;
    wall_calculator.updateWall(wall, time);

    // then
    actual_position = wall.getPosition();
    expected_position = 40;

    ASSERT_EQ(expected_position, actual_position);

    expected_velocity = 0;
    actual_velocity = wall.getVelocity();

    ASSERT_NEAR(expected_velocity, actual_velocity, 0.001);

    // when
    time = 0.75;
    wall_calculator.updateWall(wall, time);

    // then
    actual_position = wall.getPosition();
    expected_position = 50;

    ASSERT_EQ(expected_position, actual_position);

    expected_velocity = 62.831856;
    actual_velocity = wall.getVelocity();

    ASSERT_FLOAT_EQ(expected_velocity, actual_velocity);

    // when
    time = 1;
    wall_calculator.updateWall(wall, time);

    // then
    actual_position = wall.getPosition();
    expected_position = 60;

    ASSERT_EQ(expected_position, actual_position);

    expected_velocity = 0;
    actual_velocity = wall.getVelocity();

    ASSERT_NEAR(expected_velocity, actual_velocity, 0.001);
}