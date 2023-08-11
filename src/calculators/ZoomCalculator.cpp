#include "ZoomCalculator.h"

void ZoomCalculator::zoomIn(Objects &objects)
{
    scale_factor *= 2;

    zoom(objects, scale_factor);
}

void ZoomCalculator::zoomOut(Objects &objects)
{
    scale_factor *= 0.5;

    zoom(objects, scale_factor);
}

void ZoomCalculator::noZoom(Objects &objects)
{
    zoom(objects, scale_factor);
}

void ZoomCalculator::zoom(Objects &objects, const float scale_factor)
{
    for (Particle &particle : objects.particles)
    {
        const int actual_radius = particle.getRadius();
        particle.setDisplayRadius(scale_factor * actual_radius);

        const Vector displacement = particle.getPosition() - center;
        particle.setDisplayPosition(center + scale_factor * displacement);
    }

    for (Dot &dot : objects.dot_data.dots)
    {
        const Vector displacement = dot.getPosition() - center;
        dot.setDisplayPosition(center + scale_factor * displacement);
    }

    zoomRocket(objects.rocket, scale_factor);
}

void ZoomCalculator::zoomRocket(Rocket &rocket, const float scale_factor)
{
    const int initial_width = rocket.getWidth();
    rocket.setDisplayWidth(scale_factor * initial_width);

    const int initial_height = rocket.getHeight();
    rocket.setDisplayHeight(scale_factor * initial_height);

    const Vector displacement = rocket.getPosition() - center;
    const Vector display_position = center + scale_factor * displacement;
    rocket.setDisplayPosition(display_position);

    for (Engine &engine : rocket.engines)
    {
        const Vector start_disp = engine.display_line[0] - center;
        const Vector end_disp = engine.display_line[1] - center;

        const Vector start_pos = center + scale_factor * start_disp;
        const Vector end_pos = center + scale_factor * end_disp;

        engine.display_line = {start_pos, end_pos};
    }
}
