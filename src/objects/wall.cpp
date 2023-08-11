#include "Wall.h"

void Wall::setupWall(direction input_wall_orientation, wallLimitType input_wall_limit_type, float input_position, int input_length)
{
    orientation = input_wall_orientation;
    limit_type = input_wall_limit_type;
    position = input_position;
    length = input_length;

    if (orientation == x)
    {
        position_x_1 = 0;
        position_y_1 = position;

        position_x_2 = length;
        position_y_2 = position;

        velocity_direction = y;
    }
    else
    {
        position_x_1 = position;
        position_y_1 = 0;

        position_x_2 = position;
        position_y_2 = length;

        velocity_direction = x;
    }
}

direction Wall::getOrientation() const
{
    return orientation;
}

wallLimitType Wall::getLimitType() const
{
    return limit_type;
}

int Wall::getLength() const
{
    return length;
}

void Wall::setPosition(float input_position)
{
    position = input_position;
    if (orientation == x)
    {
        position_y_1 = position;
        position_y_2 = position;
    }
    else
    {
        position_x_1 = position;
        position_x_2 = position;
    }
}

float Wall::getPosition() const
{
    return position;
}

void Wall::setVelocity(float input_velocity)
{
    velocity = input_velocity;
}

float Wall::getVelocity() const
{
    return velocity;
}

float Wall::getTimeSinceLastUpdated(float time_now)
{
    float time_since_last_update = 0;

    if (time_has_been_set)
    {
        time_since_last_update = time_now - time_last_updated;
    }

    previous_time_since_last_updated = time_since_last_update;
    return time_since_last_update;
}

void Wall::setTimeLastUpdated(float time_now)
{
    time_has_been_set = true;
    time_last_updated = time_now;
}

float Wall::getPreviousTimeSinceLastUpdated() const
{
    return previous_time_since_last_updated;
}

int Wall::getPosition_x_1() const
{
    return position_x_1;
}

int Wall::getPosition_y_1() const
{
    return position_y_1;
}

int Wall::getPosition_x_2() const
{
    return position_x_2;
}

int Wall::getPosition_y_2() const
{
    return position_y_2;
}

direction Wall::getVelocityDirection() const
{
    return velocity_direction;
}

void Wall::setOscillation(int input_equilibirum_position, int input_amplitude, float input_time_period)
{
    oscillation_equilibrium_position = input_equilibirum_position;
    is_oscillating = true;
    oscillation_amplitude = input_amplitude;
    oscillation_time_period = input_time_period;
}

bool Wall::getIsOscillating() const
{
    return is_oscillating;
}

int Wall::getOscillationEquilibriumPosition() const
{
    return oscillation_equilibrium_position;
}

int Wall::getOscillationAmplitude() const
{
    return oscillation_amplitude;
}

float Wall::getOscillationTimePeriod() const
{
    return oscillation_time_period;
}

std::ostream &operator<<(std::ostream &os, const Wall &wall)
{
    os << "pos: " << wall.getPosition() << "\n"
    << "x_1: " << wall.getPosition_x_1() << "\n"
    << "x_2: " << wall.getPosition_x_2() << "\n"
    << "y_1: " << wall.getPosition_y_1() << "\n"
    << "y_2: " << wall.getPosition_y_2() << "\n"
    << "length: " << wall.getLength() << "\n"
    << "limitType: " << wall.getLimitType() << "\n"
    << "orientation: " << wall.getOrientation() << "\n"
    << "velocity: " << wall.getVelocity() << "\n"
    << "direction: " << wall.getVelocityDirection() << "\n"
    << "is_oscilating: " << wall.getIsOscillating() << "\n";

    return os;
}
