#ifndef OBJECTS_H
#define OBJECTS_H

#include "Dot.h"
#include "Rocket.h"
#include "Wall.h"
#include "Particle.h"
#include "RocketData.h"

#include <vector>

struct Objects
{
    std::vector<Particle> particles;
    DotData dot_data;
    Rocket rocket;
    std::vector<Wall> walls = {Wall(), Wall(), Wall(), Wall()};
    RocketData rocket_data;
};

struct BoxDimensions
{
    int width = 3640;
    int height = 1800;
    BoxDimensions(const int input_width, const int input_height)
    {
        width = input_width;
        height = input_height;
    }
    BoxDimensions(){}
};

#endif