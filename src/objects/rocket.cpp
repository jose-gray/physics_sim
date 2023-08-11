#include "Rocket.h"

Rocket::Rocket()
{
}

bool Rocket::getIsRocketFrame() const
{
    return is_rocket_frame;
}

void Rocket::toggleIsRocketFrame()
{
    is_rocket_frame = !is_rocket_frame;
}
