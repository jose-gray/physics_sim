#include "RocketCalculator.h"
#include <array>

void RocketCalculator::updateRocket(Rocket &rocket, const LinearParticle &particle)
{
    rocket.setCom(rocket.getPosition());
    calculateKeyPressAcceleration(rocket, particle);
    calculateVertices(rocket);
}

void RocketCalculator::returnRocketHome(Rocket &rocket)
{
    rocket.setPosition(0, 0);
    rocket.setVelocity(0, 0);
    rocket.setAcceleration(0, 0);

    rocket.setAngle(0);
    rocket.setVelocity_Angular(0);
    rocket.setAcceleration_Angular(0);
}

void RocketCalculator::calculateVertices(Rocket &rocket)
{
    const float half_width = rocket.getDisplayWidth() / 2;
    const float half_height = rocket.getDisplayHeight() / 2;

    std::array<Vector, 4> vertices;
    vertices[0] = Vector{half_width, half_height};
    vertices[1] = Vector{-half_width, half_height};
    vertices[2] = Vector{-half_width, -half_height};
    vertices[3] = Vector{half_width, -half_height};

    const float angle = rocket.getAngle();
    const Vector position = rocket.getDisplayPosition();
    for (Vector &vertex : vertices)
    {
        vertex.rotateVector(angle);
        vertex += position;
    }

    rocket.setVertices(vertices);
};

void RocketCalculator::calculateKeyPressAcceleration(Rocket &rocket, const LinearParticle &particle)
{
    for (Engine &engine : rocket.engines)
    {
        if (engine.is_on)
        {
            const float boost_factor = rocket.boost_mode ? 5 : 1;
            handleEngineOn(rocket, boost_factor, engine);
        }
    }
    // TurnOffEngines(rocket);

    if (rocket.stabiliserOn)
    {
        stabilise(rocket);
    }
    else if (rocket.straightnerOn)
    {
        straighten(rocket);
    }
    else if (rocket.circularOrbitOn)
    {
        circularOrbit(rocket, particle);
    }
}

void RocketCalculator::TurnOffEngines(Rocket &rocket)
{
    for (Engine &engine : rocket.engines)
    {
        engine.is_on = false;
    }
}

void RocketCalculator::straighten(Rocket &rocket)
{
    const float w = rocket.getVelocity_Angular();
    const float o = fmod(rocket.getAngle(), 2 * PI) + PI / 2;
    const float o_v = calculateAngle(rocket.getVelocity());
    const float d_o = o - o_v;
    const float x = w + d_o;

    couplaEngines(rocket, x);
}

void RocketCalculator::stabilise(Rocket &rocket)
{
    const float w = rocket.getVelocity_Angular();
    couplaEngines(rocket, w);
}

void RocketCalculator::circularOrbit(Rocket &rocket, const LinearParticle &particle)
{
    const Vector x_rocket = rocket.getPosition();
    const Vector x_particle = particle.getPosition();
    Vector x = x_particle - x_rocket;
    const float r = x.getMagnitude();
    const float M = particle.getMass();
    const float speed_aim = sqrt(M / r);

    x.rotateVector(3 * PI / 2);
    const Vector v_aim = speed_aim * x / r;
    const Vector v = rocket.getVelocity();
    const Vector v_dif = v_aim - v;
    linearEngines(rocket, v_dif * 0.01);

    const float o = fmod(rocket.getAngle(), 2 * PI) + PI / 2;
    const float o_aim = fmod(calculateAngle(v_aim), 2 * PI);
    const float d_o = o_aim - o;

    const float w = rocket.getVelocity_Angular();
    const float w_aim = sqrt(M / pow(r, 3));
    const float d_w = w_aim - w;

    const float something = 2 * d_w + 0.25 * d_o;
    couplaEngines(rocket, -1 * something);
}

void RocketCalculator::couplaEngines(Rocket &rocket, const float strength_factor)
{
    const int i = strength_factor > 0 ? 1 : 3;
    const int j = strength_factor > 0 ? 9 : 7;
    rocket.engines[i].is_on = true;
    rocket.engines[j].is_on = true;
    handleEngineOn(rocket, abs(strength_factor), rocket.engines[i]);
    handleEngineOn(rocket, abs(strength_factor), rocket.engines[j]);
}

void RocketCalculator::linearEngines(Rocket &rocket, const Vector strength_factor)
{
    const int i = strength_factor.getx() > 0 ? 6 : 4;
    const int j = strength_factor.gety() > 0 ? 8 : 2;
    rocket.engines[i].is_on = true;
    rocket.engines[j].is_on = true;
    handleEngineOn(rocket, abs(strength_factor.getx()), rocket.engines[i]);
    handleEngineOn(rocket, abs(strength_factor.gety()), rocket.engines[j]);
}

void RocketCalculator::handleEngineOn(Rocket &rocket, const float strength_factor, Engine &engine)
{
    addForceFromEngine(rocket, strength_factor, engine);
    updateEngineLine(rocket, strength_factor, engine);
}

void RocketCalculator::addForceFromEngine(Rocket &rocket, const float strength_factor, const Engine &engine)
{
    Vector engine_position = engine.base_force.b;
    engine_position.rotateVector(rocket.getAngle());
    engine_position += rocket.getPosition();

    Vector F = engine.base_force.F;
    F.rotateVector(rocket.getAngle());

    Force force;
    force.b = engine_position;
    force.F = strength_factor * F;

    rocket.addForce(force);
}

void RocketCalculator::updateEngineLine(Rocket &rocket, const float strength_factor, Engine &engine)
{
    Vector start = engine.initial_display_line[0];
    Vector end = engine.initial_display_line[1];

    Vector line = sqrt(strength_factor) * (end - start);
    end = start + line;

    start.rotateVector(rocket.getAngle());
    end.rotateVector(rocket.getAngle());

    start += rocket.getPosition();
    end += rocket.getPosition();

    engine.display_line = {start, end};
}
