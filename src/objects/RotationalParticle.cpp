#include "RotationalParticle.h"

Vector RotationalParticle::getDirectionVector() const
{
    Vector direction_vector = {1, 0};
    direction_vector.rotateVector(angle);
    return direction_vector;
};
