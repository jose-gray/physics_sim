#ifndef Dot_H
#define Dot_H

#include "../vector.h"
#include <vector>

class Dot
{
public:
    Dot() : position(0, 0), time_created(0){};
    Dot(Vector position, float time_created) : position(position), time_created(time_created){};
    float getTimeCreated() const { return time_created; };
    void setTimeCreated(const float input_time) { time_created = input_time; };
    Vector getPosition() const { return position; };
    void setPosition(const Vector input_position) { position = input_position; };
    void setPosition(const float x, const float y) { position = {x, y}; };
    Vector getDisplayPosition() const { return display_position; };
    void setDisplayPosition(const Vector input_display_position) { display_position = input_display_position; };
    void setDisplayPosition(const float x, const float y) { display_position = {x, y}; };

private:
    Vector position;
    float time_created;
    Vector display_position = position;
};

struct DotData
{
    std::vector<Dot> dots;
    int particle_to_follow_index = 0;
};

#endif