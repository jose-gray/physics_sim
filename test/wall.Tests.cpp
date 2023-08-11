#include <gtest/gtest.h>

#include "../src/objects/Wall.h"

TEST(wall, getPosition_returns_defualt_of_zero)
{
    // given
    Wall wall;

    // when
    float actual_position = wall.getPosition();

    // then
    float expected_position = 0;
    ASSERT_EQ(expected_position, actual_position);
}

TEST(wall, setPosition)
{
    // given
    Wall wall;

    // when
    wall.setPosition(100);

    // then
    float actual_position = wall.getPosition();

    float expected_position = 100;
    ASSERT_EQ(expected_position, actual_position);
}

TEST(wall, setPosition_also_updates_end_points_horizontal)
{
    // given
    Wall wall;

    direction orientation = x;
    wallLimitType limit_type = min;
    const int starting_position = 50;
    const int length = 50;

    wall.setupWall(orientation, limit_type, starting_position, length);

    // when
    const int new_position = 100;

    wall.setPosition(new_position);

    // then
    const int expected_x_1 = 0;
    const int actual_x_1 = wall.getPosition_x_1();

    ASSERT_EQ(expected_x_1, actual_x_1);

    const int expected_y_1 = new_position;
    const int actual_y_1 = wall.getPosition_y_1();

    ASSERT_EQ(expected_y_1, actual_y_1);

    const int expected_x_2 = length;
    const int actual_x_2 = wall.getPosition_x_2();

    ASSERT_EQ(expected_x_2, actual_x_2);

    const int expected_y_2 = new_position;
    const int actual_y_2 = wall.getPosition_y_2();

    ASSERT_EQ(expected_y_2, actual_y_2);
}

TEST(wall, setPosition_also_updates_end_points_vertical)
{
    // given
    Wall wall;

    direction orientation = y;
    wallLimitType limit_type = min;
    const int starting_position = 50;
    const int length = 50;

    wall.setupWall(orientation, limit_type, starting_position, length);

    // when
    const int new_position = 100;

    wall.setPosition(new_position);

    // then
    const int expected_x_1 = new_position;
    const int actual_x_1 = wall.getPosition_x_1();

    ASSERT_EQ(expected_x_1, actual_x_1);

    const int expected_y_1 = 0;
    const int actual_y_1 = wall.getPosition_y_1();

    ASSERT_EQ(expected_y_1, actual_y_1);

    const int expected_x_2 = new_position;
    const int actual_x_2 = wall.getPosition_x_2();

    ASSERT_EQ(expected_x_2, actual_x_2);

    const int expected_y_2 = length;
    const int actual_y_2 = wall.getPosition_y_2();

    ASSERT_EQ(expected_y_2, actual_y_2);
}

TEST(wall, getVelocity_returns_zero_if_not_set)
{
    // given
    Wall wall;

    // when
    float actual_velocity_default = wall.getVelocity();

    // then
    float expected_velocity_default = 0;
    ASSERT_FLOAT_EQ(expected_velocity_default, actual_velocity_default);
}

TEST(wall, setVelocity)
{
    // given
    Wall wall;

    // when
    wall.setVelocity(100);

    // then
    float actual_velocity = wall.getVelocity();

    float expected_velocity = 100;
    ASSERT_EQ(expected_velocity, actual_velocity);
}

TEST(wall, getTimeSinceLastUpdated_when_not_set)
{
    // given
    Wall wall;

    // when
    float actual_time_since_last_updated = wall.getTimeSinceLastUpdated(100);

    // then
    float expected_time_since_last_update = 0;
    ASSERT_EQ(expected_time_since_last_update, actual_time_since_last_updated);
}

TEST(wall, setTimeLastUpdated)
{
    // given
    Wall wall;

    // when
    wall.setTimeLastUpdated(75);

    // then
    float actual_time_since_last_updated = wall.getTimeSinceLastUpdated(100);

    float expected_time_since_last_update = 25;
    ASSERT_EQ(expected_time_since_last_update, actual_time_since_last_updated);
}

TEST(wall, getPreviousTimeSinceLastUpdated)
{
    // given
    Wall wall;
    wall.setTimeLastUpdated(10);
    float throwaway = wall.getTimeSinceLastUpdated(15);

    // when
    float actual_previous_time_since_last_updated = wall.getPreviousTimeSinceLastUpdated();

    // then
    float expected_previous_time_since_last_updated = 5;

    ASSERT_EQ(expected_previous_time_since_last_updated, actual_previous_time_since_last_updated);
}

TEST(wall, setupWall_sets_correct_things)
{
    // given
    Wall wall;

    const direction orientation = x;
    const wallLimitType limit_type = min;
    const float position = 10;
    const float length = 50;

    // when
    wall.setupWall(orientation, limit_type, position, length);

    // then
    const direction expected_orientation = orientation;
    const direction actual_direction = wall.getOrientation();

    ASSERT_EQ(expected_orientation, actual_direction);

    const wallLimitType expected_limit_type = limit_type;
    const wallLimitType actaul_limit_type = wall.getLimitType();

    ASSERT_EQ(expected_limit_type, actaul_limit_type);

    const float expected_position = position;
    const float actual_position = wall.getPosition();

    ASSERT_EQ(expected_position, actual_position);

    const float expected_length = length;
    const float actual_length = wall.getLength();

    ASSERT_EQ(expected_length, actual_length);
}

TEST(wall, co_ords_of_ends_horizontal)
{
    // given
    Wall wall;

    const direction orientation = x;
    const wallLimitType limit_type = min;
    const float position = 10;
    const int length = 100;

    // when
    wall.setupWall(orientation, limit_type, position, length);

    // then
    const int expected_x_1 = 0;
    const int actual_x_1 = wall.getPosition_x_1();

    ASSERT_EQ(expected_x_1, actual_x_1);

    const int expected_y_1 = position;
    const int actual_y_1 = wall.getPosition_y_1();

    ASSERT_EQ(expected_y_1, actual_y_1);

    const int expected_x_2 = length;
    const int actual_x_2 = wall.getPosition_x_2();

    ASSERT_EQ(expected_x_2, actual_x_2);

    const int expected_y_2 = position;
    const int actual_y_2 = wall.getPosition_y_2();

    ASSERT_EQ(expected_y_2, actual_y_2);
}

TEST(wall, co_ords_of_ends_vertical)
{
    // given
    Wall wall;

    const direction orientation = y;
    const wallLimitType limit_type = max;
    const float position = 15;
    const int length = 250;

    // when
    wall.setupWall(orientation, limit_type, position, length);

    // then
    const int expected_x_1 = position;
    const int actual_x_1 = wall.getPosition_x_1();

    ASSERT_EQ(expected_x_1, actual_x_1);

    const int expected_y_1 = 0;
    const int actual_y_1 = wall.getPosition_y_1();

    ASSERT_EQ(expected_y_1, actual_y_1);

    const int expected_x_2 = position;
    const int actual_x_2 = wall.getPosition_x_2();

    ASSERT_EQ(expected_x_2, actual_x_2);

    const int expected_y_2 = length;
    const int actual_y_2 = wall.getPosition_y_2();

    ASSERT_EQ(expected_y_2, actual_y_2);
}

TEST(wall, direction_of_motion_horizontal_wall)
{
    // given
    Wall wall;

    const direction orientation = x;
    const wallLimitType limit_type = min;
    const float position = 10;
    const int length = 100;

    // when
    wall.setupWall(orientation, limit_type, position, length);

    // then

    const direction expected_velocity_direction = y;
    const direction actual_velocity_direction = wall.getVelocityDirection();

    ASSERT_EQ(expected_velocity_direction, actual_velocity_direction);
}

TEST(wall, direction_of_motion_vertical_wall)
{
    // given
    Wall wall;

    const direction orientation = y;
    const wallLimitType limit_type = max;
    const float position = 15;
    const int length = 250;

    // when
    wall.setupWall(orientation, limit_type, position, length);

    // then

    const direction expected_velocity_direction = x;
    const direction actual_velocity_direction = wall.getVelocityDirection();

    ASSERT_EQ(expected_velocity_direction, actual_velocity_direction);
}

TEST(wall, isOscillation_default_is_false)
{
    // setup
    Wall wall;

    const direction orientation = y;
    const wallLimitType limit_type = max;
    const float position = 15;
    const int length = 250;
    wall.setupWall(orientation, limit_type, position, length);

    // when
    const bool actual_is_oscillating = wall.getIsOscillating();

    // then
    const bool expected_is_oscillating = false;

    ASSERT_EQ(expected_is_oscillating, actual_is_oscillating);
}

TEST(wall, setup_oscillations)
{
    // setup
    Wall wall;

    const direction orientation = y;
    const wallLimitType limit_type = max;
    const float position = 15;
    const int length = 250;
    wall.setupWall(orientation, limit_type, position, length);

    // when
    const int equilibrium_position = 50;
    const int amplitude = 10;
    const float time_period = 0.5;
    wall.setOscillation(equilibrium_position, amplitude, time_period);

    // then
    const bool actual_is_oscillating = wall.getIsOscillating();
    const bool expected_is_oscillating = true;

    ASSERT_EQ(expected_is_oscillating, actual_is_oscillating);

    const int actual_equilibrium_position = wall.getOscillationEquilibriumPosition();
    const int expected_equilibrium_position = equilibrium_position;

    ASSERT_EQ(expected_equilibrium_position, actual_equilibrium_position);

    const int actual_amplitude = wall.getOscillationAmplitude();
    const int expected_amplitude = amplitude;

    ASSERT_EQ(expected_amplitude, actual_amplitude);

    const float actual_time_period = wall.getOscillationTimePeriod();
    const float expected_time_period = time_period;

    ASSERT_EQ(expected_time_period, actual_time_period);
}
