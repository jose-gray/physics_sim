#include "../generated/TagVersion.h"
#include "Demos.h"
#include "Display.h"

int main(void)
{
    demoChoices demo_choice = rocket_orbits;

    Demos demos(demo_choice);

    Objects objects;
    BoxDimensions box_dimensions;
    demoMode demo_mode;
    demos.setIntialConditions(objects, box_dimensions, demo_mode);

    Display display{demo_mode, box_dimensions};

    display.run(objects);
}
