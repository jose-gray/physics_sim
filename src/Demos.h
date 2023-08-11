#pragma once
#include "Display.h"

class Demos
{
private:
    demoChoices demo_choice;
    
    // actual demos
    // thermo
    void diffusionDemo(Objects &objects, BoxDimensions &box_dimensions);
    void sizedParticlesDemo(Objects &objects, BoxDimensions &box_dimensions);
    void gasInGravity(Objects &objects, BoxDimensions &box_dimensions);
    void idealGasDemo(Objects &objects, BoxDimensions &box_dimensions);
    void soundWavesDemo(Objects &objects, BoxDimensions &box_dimensions);

    // astro
    void orbitsDemo(Objects &objects, BoxDimensions &box_dimensions);
    void lotsOfParticlesDemo(Objects &objects, BoxDimensions &box_dimensions);
    void binaryDemo(Objects &objects, BoxDimensions &box_dimensions);
    void sunEarthMoonDemo(Objects &objects, BoxDimensions &box_dimensions);

    // rocket
    void rocketDemo(Objects &objects, BoxDimensions &box_dimensions);
    void rocketOrbitsDemo(Objects &objects, BoxDimensions &box_dimensions);

    // ions
    void ionLatticeDemo(Objects &objects, BoxDimensions &box_dimensions);
    void chargeFourIonsDemo(Objects &objects, BoxDimensions &box_dimensions);
    void outerPotential(Objects &objects, BoxDimensions &box_dimensions);
    void ionTrapDemo(Objects &objects, BoxDimensions &box_dimensions);
    void allSameChargeDemo(Objects &objects, BoxDimensions &box_dimensions);

    void bugFix(Objects &objects, BoxDimensions &box_dimensions);

    // helpers
    void distributePositionsRandomly(std::vector<Particle> &particles, BoxDimensions &box_dimensions, int fill_fraction_x, int fill_fraction_y);
    void distributeVelocitiesRandomly(std::vector<Particle> &particles, int max_velocity);
    void distributeRadiusRandomly(std::vector<Particle> &particles, int min_radius, int max_radius);
    void setMassForConstantDensity2D(std::vector<Particle> &particles, const int density);
    void setMassForConstantDensity3D(std::vector<Particle> &particles, const int density);
    void setAllColours(std::vector<Particle> &particles, Color color);
    void initialiseWalls(std::vector<Wall> &walls, BoxDimensions &box_dimensions);
    void setupRocket(Rocket &rocket);
    void rocketMomentOfInertia(Rocket &rocket);
    void rocketEngines(Rocket &rocket);

public:
    Demos(demoChoices demo_choice);
    void setIntialConditions(Objects &objects, BoxDimensions &box_dimensions, demoMode &demo_mode);
};