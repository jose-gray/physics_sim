#ifndef RocketCalculator_H
#define RocketCalculator_H

#include "../objects/Rocket.h"
#include "../objects/Particle.h"
#include "RotationCalculator.h"
#include "keyPressManager.h"


class RocketCalculator
{
public:
    void updateRocket(Rocket &rocket, const LinearParticle &particle);
    void returnRocketHome(Rocket &rocket);

private:
    RotationCalculator rotation_calculator;

    void calculateVertices(Rocket &rocket);
    void straighten(Rocket &rocket);
    void stabilise(Rocket &rocket);
    void couplaEngines(Rocket &rocket, const float strength_factor);
    void handleEngineOn(Rocket &rocket, const float strength_factor, Engine &engine);
    void addForceFromEngine(Rocket &rocket, const float strength_factor, const Engine &engine);
    void updateEngineLine(Rocket &rocket, const float strength_factor, Engine &engine);
    void linearEngines(Rocket &rocket, const Vector strength_factor);
    void calculateKeyPressAcceleration(Rocket &rocket, const LinearParticle &particle);
    void circularOrbit(Rocket &rocket, const LinearParticle &particle);
    void TurnOffEngines(Rocket &rocket);
};

#endif
