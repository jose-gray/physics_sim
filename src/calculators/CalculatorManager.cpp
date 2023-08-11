#include "CalculatorManager.h"

void CalculatorManager::calculateUpdates(Objects &objects)
{
    newtonian_calculator.updateParticles(objects.particles, time.getCurrentTime());

    particle_collisions_calculator.updateParticles(objects.particles);

    if (demo_mode == thermo || demo_mode == ions)
    {
        for (Wall &wall : objects.walls)
        {
            const float time_now = time.getCurrentTime();
            wall_calculator.updateWall(wall, time_now);
        }
        wall_collisions_calculator.updateParticles(objects.particles, objects.walls);

        pressure_calculator.addPressureOfFrame(wall_collisions_calculator.getPressureLastFrame());
    }

    if (demo_mode == astro || demo_mode == rocket_mode)
    {
        gravity_calculator.updateForcesAndHandleCombinations(objects.particles, objects.rocket);
    }

    if (demo_mode == rocket_mode)
    {
        if (objects.rocket.getIsRocketFrame())
        {
            reference_frame_calculator.changeToRocketFrame(objects);
        }
        handleRocketKeyPresses(objects);

        const float time_now = time.getCurrentTime();
        newtonian_calculator.updateRocket(objects.rocket, time_now);

        rocket_calculator.updateRocket(objects.rocket, objects.particles[0]);
        dot_calculator.addDot(objects.dot_data, objects.rocket.getPosition(), time_now);

        const int main_planet_index = 0;
        RocketDataCalculator::updateRocketData(objects.rocket_data, objects.rocket, objects.particles[main_planet_index]);
        if (objects.rocket.getIsRocketFrame())
        {
            reference_frame_calculator.changeToRocketFrame(objects);
        }
    }
    else
    {
        const float time_now = time.getCurrentTime();
        dot_calculator.addDot(objects.dot_data, objects.particles[objects.dot_data.particle_to_follow_index].getPosition(), time_now);
    }

    if (demo_mode == ions)
    {
        coulombs_law_calculator.updateParticles(objects.particles);
    }

    handleKeyPresses(objects);
}

float CalculatorManager::getPressure() const
{
    return pressure_calculator.getPressure();
}

float CalculatorManager::getTemperature(std::vector<Particle> &particles) const
{
    return wall_collisions_calculator.getTemperature(particles);
}

void CalculatorManager::handleRocketKeyPresses(Objects &objects)
{
    key_press_manager.updateKeyPressFlags(key_press_flags);

    if (key_press_flags.switch_frame)
    {
        switchFrame(objects);
    }

    if (key_press_flags.return_to_home)
    {
        returnToHome(objects);
    }

    Rocket &rocket = objects.rocket;
    rocket.boost_mode = key_press_flags.engine_boost;

    rocket.stabiliserOn = false;
    rocket.straightnerOn = false;
    if (key_press_flags.number_pad_engine[0])
    {
        rocket.straightnerOn = true;
    }
    else if (key_press_flags.number_pad_engine[5])
    {
        rocket.stabiliserOn = true;
    }
    else if (key_press_flags.circular_orbit_toggle)
    {
        rocket.circularOrbitOn = !rocket.circularOrbitOn;
    }

    for (size_t i = 0; i < key_press_flags.number_pad_engine.size(); i++)
    {
        if(key_press_flags.number_pad_engine[0])
        {
            rocket.straightnerOn = true;
        }
        else if (key_press_flags.number_pad_engine[5])
        {
            rocket.stabiliserOn = true;
        }
        else if(key_press_flags.circular_orbit_toggle)
        {
            rocket.circularOrbitOn = !rocket.circularOrbitOn;
        }
        else
        {
            for (size_t i = 0; i < key_press_flags.number_pad_engine.size(); i++)
            {
                rocket.engines[i].is_on = key_press_flags.number_pad_engine[i];
            }
        }
    }
}

void CalculatorManager::handleKeyPresses(Objects &objects)
{
    key_press_manager.updateKeyPressFlags(key_press_flags);

    if (key_press_flags.reset_dots)
    {
        dot_calculator.resetDots(objects.dot_data);
    }

    if (key_press_flags.zoom_in)
    {
        zoom_calculator.zoomIn(objects);
    }
    else if (key_press_flags.zoom_out)
    {
        zoom_calculator.zoomOut(objects);
    }
    else
    {
        zoom_calculator.noZoom(objects);
    }
}

void CalculatorManager::switchFrame(Objects &objects)
{
    if (objects.rocket.getIsRocketFrame())
    {
        reference_frame_calculator.changeToUniverseFrame(objects);
    }
    else
    {
        reference_frame_calculator.changeToRocketFrame(objects);
    }

    objects.rocket.toggleIsRocketFrame();
}

void CalculatorManager::returnToHome(Objects &objects)
{
    if (objects.rocket.getIsRocketFrame())
    {
        reference_frame_calculator.changeToUniverseFrame(objects);

        rocket_calculator.returnRocketHome(objects.rocket);

        reference_frame_calculator.changeToRocketFrame(objects);
    }
    else
    {
        rocket_calculator.returnRocketHome(objects.rocket);
    }
}
