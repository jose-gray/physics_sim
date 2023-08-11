#pragma once
#include "LinearParticle.h"

#include <vector>

extern "C"
{
#include "raylib.h"
}

class Particle : public LinearParticle
{
private:
    float radius;

    int display_radius;

    float coefficient_of_restitution;

    float charge;

    bool is_fixed;

    Color particle_color = BLACK;

public:
    Particle();

    void setRadius(const int input_radius)
    {
        radius = input_radius;
    };
    int getRadius() const
    {
        return radius;
    };

    void setDisplayRadius(const int input_display_radius)
    {
        display_radius = input_display_radius;
    };
    int getDisplayRadius() const
    {
        return display_radius;
    };

    void setRestitution(const float input_restitution)
    {
        coefficient_of_restitution = input_restitution;
    };
    float getRestitution() const
    {
        return coefficient_of_restitution;
    };

    void setCharge(const float input_charge);
    float getCharge() const
    {
        return charge;
    };

    void fixParticle()
    {
        is_fixed = true;
    };
    bool getIsFixed() const
    {
        return is_fixed;
    };

    void setColor(const Color input_color)
    {
        particle_color = input_color;
    };
    Color getColor() const
    {
        return particle_color;
    };
};

bool operator==(const Particle &lhs, const Particle &rhs);
