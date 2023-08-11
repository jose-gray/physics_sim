#include <gtest/gtest.h>

#include "../src/calculators/DotCalculator.h"

TEST(Dots, if_dots_size_is_zero_no_dots_added)
{
    // given
    DotCalculator dot_calculator;

    DotData dot_data;

    dot_data.dots.resize(0);

    const Vector position = {25, 63};
    const float time_now = 32.56;

    // when
    dot_calculator.addDot(dot_data, position, time_now);

    // then
    ASSERT_EQ(0, dot_data.dots.size());
}

TEST(Dots, adds_dot_at_time_and_place)
{
    // given
    DotCalculator dot_calculator;

    DotData dot_data;
    dot_data.dots.resize(100);

    const Vector position = {25, 63};
    const float time_now = 32.56;

    // when
    dot_calculator.addDot(dot_data, position, time_now);

    // then
    ASSERT_EQ(position, dot_data.dots[0].getPosition());
    ASSERT_EQ(time_now, dot_data.dots[0].getTimeCreated());
}

TEST(Dots, does_not_add_dot_if_less_than_tenth_of_second_since_last_dot)
{
    // given
    DotCalculator dot_calculator;

    DotData dot_data;
    dot_data.dots.resize(100);

    const Vector position_1 = {25, 63};
    const float time_1 = 32.56;

    dot_calculator.addDot(dot_data, position_1, time_1);

    const Vector position_2 = {15, 500};
    const float time_2 = time_1 + 0.05; // not enough time

    // when
    dot_calculator.addDot(dot_data, position_2, time_2);

    // then
    const Vector zero_vector = {0, 0};

    ASSERT_EQ(zero_vector, dot_data.dots[1].getPosition());
    ASSERT_EQ(0, dot_data.dots[1].getTimeCreated());
}

TEST(Dots, when_full_adds_back_in_zeroth_index)
{
    // given
    DotCalculator dot_calculator;

    DotData dot_data;
    dot_data.dots.resize(100);

    const Vector position_1 = {25, 63};
    float time = 32.56;

    for (int i = 0; i < 100; i++)
    {
        dot_calculator.addDot(dot_data, position_1, time);
        time++;
    }

    const Vector position_2 = {15, 500};

    // when
    dot_calculator.addDot(dot_data, position_2, time);

    // then
    ASSERT_EQ(position_2, dot_data.dots[0].getPosition());
    ASSERT_EQ(time, dot_data.dots[0].getTimeCreated());
    ASSERT_EQ(100, dot_data.dots.size());
}

TEST(Dots, reset_dots_resets)
{
    // given
    DotCalculator dot_calculator;

    DotData dot_data;
    dot_data.dots.resize(100);

    const Vector position_1 = {25, 63};
    float time = 32.56;

    for (int i = 0; i < 100; i++)
    {
        dot_calculator.addDot(dot_data, position_1, time);
        time++;
    }

    const Vector position_2 = {15, 500};

    // when
    dot_calculator.resetDots(dot_data);

    // then
    const Vector zero_vector = {0, 0};

    ASSERT_EQ(zero_vector, dot_data.dots[0].getPosition());
    ASSERT_EQ(0, dot_data.dots[1].getTimeCreated());
}
