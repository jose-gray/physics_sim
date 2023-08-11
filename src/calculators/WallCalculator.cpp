#include "WallCalculator.h"

#ifndef PI
#define PI 3.14159265358979323846f // Required as PI is not always defined in math.h
#endif

void WallCalculator::updateWall(Wall &wall, float time_now)
{
    getWallVariables(wall, time_now);

    if (is_oscillating)
    {
        updatePositionOscillations(wall, time_now);
        updateVelocityOscillations(wall, time_now);
    }
    else
    {
        position += velocity * time_increment;
        wall.setPosition(position);
    }

    wall.setTimeLastUpdated(time_now);
}

void WallCalculator::getWallVariables(Wall &wall, float time_now)
{
    position = wall.getPosition();
    velocity = wall.getVelocity();
    time_increment = wall.getTimeSinceLastUpdated(time_now);
    is_oscillating = wall.getIsOscillating();
}

void WallCalculator::updatePositionOscillations(Wall &wall, float time_now)
{
    const int equlibrium_position = wall.getOscillationEquilibriumPosition();
    const int amplitude = wall.getOscillationAmplitude();
    const float time_period = wall.getOscillationTimePeriod();

    const float starting_phase = PI / 2;

    position = equlibrium_position + amplitude * sin(2 * PI * time_now / time_period + starting_phase);

    wall.setPosition(position);
}

void WallCalculator::updateVelocityOscillations(Wall &wall, float time_now)
{
    const int amplitude = wall.getOscillationAmplitude();
    const float time_period = wall.getOscillationTimePeriod();

    const float starting_phase = PI / 2;

    const float velocity = (amplitude * 2 * PI / time_period) * cos(2 * PI * time_now / time_period + starting_phase);

    wall.setVelocity(velocity);
}
