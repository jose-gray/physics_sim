#include <iostream>
#ifndef WALL_H
#define WALL_H

enum direction
{
    x,
    y,
};

enum wallLimitType
{
    max,
    min,
};

class Wall
{
private:
    direction orientation;

    wallLimitType limit_type;

    float position = 0;

    int position_x_1 = 0;
    int position_y_1 = 0;

    int position_x_2 = 0;
    int position_y_2 = 0;

    float length = 0;

    float velocity = 0;
    direction velocity_direction;

    bool time_has_been_set = false;
    float time_last_updated = 0;

    float previous_time_since_last_updated = 0;

    float force_on_wall;

    bool is_oscillating = false;
    int oscillation_equilibrium_position;
    int oscillation_amplitude;
    float oscillation_time_period;

public:
    void setupWall(direction input_wall_orientation, wallLimitType input_wall_limit_type, float input_position, int input_length);

    direction getOrientation() const;

    wallLimitType getLimitType() const;

    void setPosition(float input_position);
    float getPosition() const;

    int getPosition_x_1() const;
    int getPosition_y_1() const;
    int getPosition_x_2() const;
    int getPosition_y_2() const;

    void setVelocity(float input_velocity);
    float getVelocity() const;
    direction getVelocityDirection() const;

    void setTimeLastUpdated(float time_now);
    float getTimeSinceLastUpdated(float time_now);

    float getPreviousTimeSinceLastUpdated() const;

    int getLength() const;

    void setOscillation(int input_equilibirum_position, int input_amplitude, float input_time_period);
    bool getIsOscillating() const;
    int getOscillationEquilibriumPosition() const;
    int getOscillationAmplitude() const;
    float getOscillationTimePeriod() const;
};

std::ostream &operator<<(std::ostream &os, const Wall &wall);

#endif