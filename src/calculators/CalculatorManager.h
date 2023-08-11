#include "../Time.h"
#include "../DemoModes.h"
#include "WallCollisionsCalculator.h"
#include "WallCalculator.h"
#include "ParticleCollisionsCalculator.h"
#include "GravityCalculator.h"
#include "CoulombsLawCalculator.h"
#include "PressureCalculator.h"
#include "RocketCalculator.h"
#include "ReferenceFrameCalculator.h"
#include "keyPressManager.h"
#include "DotCalculator.h"
#include "ZoomCalculator.h"
#include "NewtonianCalculator.h"
#include "RocketDataCalculator.h"

class CalculatorManager
{
public:
    CalculatorManager(demoMode demo_mode, BoxDimensions box_dimensions) : demo_mode(demo_mode), box_dimensions(box_dimensions){};
    void calculateUpdates(Objects &objects);
    float getPressure() const;
    float getTemperature(std::vector<Particle> &particles) const;

private:
    const demoMode demo_mode;
    const BoxDimensions box_dimensions;
    const Vector center = {(float)box_dimensions.width / 2, (float)box_dimensions.height / 2};

    WallCollisionsCalculator wall_collisions_calculator;
    PressureCalculator pressure_calculator;
    WallCalculator wall_calculator;
    ParticleCollisionsCalculator particle_collisions_calculator;
    GravityCalculator gravity_calculator;
    CoulombsLawCalculator coulombs_law_calculator;
    RocketCalculator rocket_calculator;
    ReferenceFrameCalculator reference_frame_calculator{box_dimensions};
    KeyPressManager key_press_manager;
    KeyPressFlags key_press_flags;
    DotCalculator dot_calculator;
    ZoomCalculator zoom_calculator{center};
    NewtonianCalculator newtonian_calculator;

    Time time;

    void handleKeyPresses(Objects &objects);
    void handleRocketKeyPresses(Objects &objects);
    void switchFrame(Objects &objects);
    void returnToHome(Objects &objects);
};
