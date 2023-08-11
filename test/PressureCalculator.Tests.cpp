#include <gtest/gtest.h>

#include "../src/calculators/PressureCalculator.h"

TEST(PressureCalculator, default_pressure_is_zero)
{
    // given
    PressureCalculator pressure_calculator;

    // when
    const float actual_pressure = pressure_calculator.getPressure();

    // then
    const float expected_pressure = 0;

    ASSERT_EQ(expected_pressure, actual_pressure);
}

TEST(PressureCalculator, adding_single_frames_pressure)
{
    // given
    PressureCalculator pressure_calculator;

    // when
    pressure_calculator.addPressureOfFrame(10);

    // then
    const float actual_pressure = pressure_calculator.getPressure();
    const float expected_pressure = 10;

    ASSERT_EQ(expected_pressure, actual_pressure);
}

TEST(PressureCalculator, adding_two_frames_pressure_gives_average)
{
    // given
    PressureCalculator pressure_calculator;

    // when
    pressure_calculator.addPressureOfFrame(10);
    pressure_calculator.addPressureOfFrame(20);

    // then
    const float actual_pressure = pressure_calculator.getPressure();
    const float expected_pressure = 15;

    ASSERT_EQ(expected_pressure, actual_pressure);
}

TEST(PressureCalculator, adding_more_than_400_frames_pressure_gives_rolling_avg)
{
    // given
    PressureCalculator pressure_calculator;

    // when
    for (int i = 0; i < 400; i++)
    {
        pressure_calculator.addPressureOfFrame(10);
    }
    for (int i = 0; i < 200; i++)
    {
        pressure_calculator.addPressureOfFrame(20);
    }

    // then
    const float actual_pressure = pressure_calculator.getPressure();
    const float expected_pressure = 15;

    ASSERT_EQ(expected_pressure, actual_pressure);
}