#include "DotCalculator.h"

void DotCalculator::addDot(DotData &dot_data, const Vector position, const float time_now)
{
    if(dot_data.dots.size() == 0)
    {
        return;
    }
        
    const float min_time_between_dots = 0.05;

    if (time_now - dot_data.dots[last_index].getTimeCreated() > min_time_between_dots)
    {
        const int index = dots_added_count % dot_data.dots.size();
        dot_data.dots[index].setPosition(position);
        dot_data.dots[index].setTimeCreated(time_now);

        last_index = index;
        dots_added_count++;
    }
}

void DotCalculator::resetDots(DotData &dot_data)
{
    for(Dot &dot : dot_data.dots)
    {
        dot.setPosition({0, 0});
        dot.setTimeCreated(0);
    }
    dots_added_count = 0;
    last_index = 0;
}