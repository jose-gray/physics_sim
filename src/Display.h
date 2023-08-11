#pragma once
#include "calculators/CalculatorManager.h"
#include "calculators/SigFigsCalculator.h"
#include "Demos.h"

#define WINDOW_X_POSITION 100
#define WINDOW_Y_POSITION 150

class Display
{
public:
    Display(demoMode demo_mode, BoxDimensions box_dimensions) : demo_mode(demo_mode), box_dimensions(box_dimensions){};

    void run(Objects &objects);

    void intialiseWindow();

private:
    const demoMode demo_mode;
    const BoxDimensions box_dimensions;

    CalculatorManager calculator_manager{demo_mode, box_dimensions};

    sigFigsCalculator sig_figs_calculator;

    Time time;

    void drawParticle(Particle &particle);

    void drawWall(Wall &wall);

    void drawRocket(Rocket &rocket);

    void drawDot(Dot &dot);

    void drawTemperature(float T);

    void drawPressure(float P);

    void drawRocketData(const RocketData &rocket_data);

    void drawRocketLineToPlanet(const Rocket &rocket, const RocketData &rocket_data);

    Vector convertToRaylibCoords(const Vector vector);
};
