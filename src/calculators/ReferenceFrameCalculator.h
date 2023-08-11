#ifndef REFERENCEFRAMECALCULATOR_H
#define REFERENCEFRAMECALCULATOR_H

#include "RotationCalculator.h"
#include "../objects/Objects.h"

class ReferenceFrameCalculator
{
    public:
    ReferenceFrameCalculator(BoxDimensions box_dimensions) : box_dimensions(box_dimensions){};
    void changeToRocketFrame(Objects &objects);
    void changeToUniverseFrame(Objects &objects);

    private:
    RotationCalculator rotation_calculator;

    Vector cumulativeDisplacement  = {0, 0};
    float cumulativeAngleOfRotation = 0;

    const BoxDimensions box_dimensions;
    const Vector center = {(float)box_dimensions.width/2, (float)box_dimensions.height/2};
};

#endif
