#ifndef DotCalculator_H
#define DotCalculator_H

#include "../objects/dot.h"

class DotCalculator
{
public:
    void addDot(DotData &dot_data, const Vector position, const float time_now);
    void resetDots(DotData &dot_data);

private:
    int dots_added_count = 0;
    int last_index = 0;
};

#endif