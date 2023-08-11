#ifndef RotationCalculator_H
#define RotationCalculator_H

#include "../objects/Objects.h"

class RotationCalculator
{
public:
    void rotateParticleAboutPoint(Vector center_of_rotation, float angle, LinearParticle &particle);
    void rotateParticleAboutPoint(Vector center_of_rotation, float cos_angle, float sin_angle, LinearParticle &particle);

    void rotateParticleAboutPoint(Vector center_of_rotation, float angle, Dot &dot);
    void rotateParticleAboutPoint(Vector center_of_rotation, float cos_angle, float sin_angle, Dot &dot);

    void rotateParticleAboutPoint(Vector center_of_rotation, float angle, RotationalParticle &particle);
};

#endif
