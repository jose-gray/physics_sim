#include "PressureCalculator.h"

#include <iostream>

PressureCalculator::PressureCalculator()
{
    rolling_average_pressure = 0;
    number_of_frames = 0;
    for (int i = 0; i < number_of_frames_to_average; i++)
    {
        pressure_each_frame[i] = 0;
    }
}

float PressureCalculator::getPressure() const
{
    return rolling_average_pressure;
}

void PressureCalculator::addPressureOfFrame(float pressure)
{
    const int index = number_of_frames % number_of_frames_to_average;
    pressure_each_frame[index] = pressure;
    number_of_frames++;

    updateRollingAveragePressure();
}

void PressureCalculator::updateRollingAveragePressure()
{
    float sum_pressures = 0;
    for (int i = 0; i < number_of_frames_to_average; i++)
    {
        sum_pressures += pressure_each_frame[i];
    }

    if (number_of_frames < number_of_frames_to_average)
    {
        rolling_average_pressure = sum_pressures / number_of_frames;
    }
    else
    {
        rolling_average_pressure = sum_pressures / number_of_frames_to_average;
    }
}