#include "Demos.h"

Demos::Demos(demoChoices input_demo_choice)
{
    demo_choice = input_demo_choice;
}

void Demos::setIntialConditions(Objects &objects, BoxDimensions &box_dimensions, demoMode &demo_mode)
{
    objects.dot_data.dots.resize(100);
    switch (demo_choice)
    {
    case diffusion:
        demo_mode = thermo;
        diffusionDemo(objects, box_dimensions);
        break;
    case different_sizes:
        demo_mode = thermo;
        sizedParticlesDemo(objects, box_dimensions);
        break;
    case ideal_gas:
        demo_mode = thermo;
        idealGasDemo(objects, box_dimensions);
        break;
    case gas_in_gravity:
        demo_mode = thermo;
        gasInGravity(objects, box_dimensions);
        break;
    case sound_waves:
        demo_mode = thermo;
        soundWavesDemo(objects, box_dimensions);
        break;
    case orbits:
        demo_mode = astro;
        orbitsDemo(objects, box_dimensions);
        break;
    case binary_orbit:
        demo_mode = astro;
        binaryDemo(objects, box_dimensions);
        break;
    case sun_earth_moon:
        demo_mode = astro;
        sunEarthMoonDemo(objects, box_dimensions);
        break;
    case many_particles:
        demo_mode = astro;
        lotsOfParticlesDemo(objects, box_dimensions);
        break;
    case ion_lattice:
        demo_mode = ions;
        ionLatticeDemo(objects, box_dimensions);
        break;
    case charge_four_ions:
        demo_mode = ions;
        chargeFourIonsDemo(objects, box_dimensions);
        break;
    case outer_potential:
        demo_mode = ions;
        outerPotential(objects, box_dimensions);
        break;
    case ion_trap:
        demo_mode = ions;
        ionTrapDemo(objects, box_dimensions);
        break;
    case all_same_charge:
        demo_mode = ions;
        allSameChargeDemo(objects, box_dimensions);
        break;
    case basic_rocket:
        demo_mode = rocket_mode;
        setupRocket(objects.rocket);
        rocketDemo(objects, box_dimensions);
        break;
    case rocket_orbits:
        demo_mode = rocket_mode;
        setupRocket(objects.rocket);
        rocketOrbitsDemo(objects, box_dimensions);
        break;
    case rocket_binary:
        demo_mode = rocket_mode;
        setupRocket(objects.rocket);
        binaryDemo(objects, box_dimensions);
        break;
    case bug_fix:
        demo_mode = astro;
        bugFix(objects, box_dimensions);
        break;
    }

    initialiseWalls(objects.walls, box_dimensions);
}

//
// demos
//

void Demos::diffusionDemo(Objects &objects, BoxDimensions &box_dimensions)
{
    box_dimensions.width = 1200;
    box_dimensions.height = 800;
    objects.particles.resize(700);
    objects.dot_data.dots.resize(500);

    const int radius = 10;
    const int speed = 200;
    const int g = 0;

    distributePositionsRandomly(objects.particles, box_dimensions, 1, 1);
    distributeVelocitiesRandomly(objects.particles, speed);

    for (Particle &particle : objects.particles)
    {
        particle.setRadius(radius);
        particle.setAcceleration(0, g);

        const float x_position = particle.getPosition()[0];

        if (x_position < box_dimensions.width / 2)
        {
            particle.setColor(RED);
        }
        else
        {
            particle.setColor(BLUE);
        }
    }
}

void Demos::sizedParticlesDemo(Objects &objects, BoxDimensions &box_dimensions)
{
    objects.particles.resize(800);
    objects.dot_data.dots.resize(500);

    const int largest_radius = 50;
    const int speed = 0;
    const int g = 100;
    const float e = 0.99;

    distributePositionsRandomly(objects.particles, box_dimensions, 1, 1);
    distributeVelocitiesRandomly(objects.particles, speed);

    size_t i = 0;
    for (Particle &particle : objects.particles)
    {
        particle.setAcceleration(0, g);
        particle.setRestitution(e);
        if (i < 4 * objects.particles.size() / 6)
        {
            particle.setColor(GREEN);
            const int radius = largest_radius * 1 / 2;
            const int mass = radius * radius * radius / 100;
            particle.setRadius(radius);
            particle.setMass(mass);
        }
        else if (i < 5 * objects.particles.size() / 6)
        {
            particle.setColor(RED);
            const int radius = largest_radius * 1 / 6;
            const int mass = radius * radius * radius / 100;
            particle.setRadius(radius);
            particle.setMass(mass);
        }
        else
        {
            particle.setColor(BLUE);
            const int radius = largest_radius;
            const int mass = radius * radius * radius / 100;
            particle.setRadius(radius);
            particle.setMass(mass);
        }
        i++;
    }
}

void Demos::idealGasDemo(Objects &objects, BoxDimensions &box_dimensions)
{
    objects.particles.resize(1600);
    objects.dot_data.dots.resize(500);

    setAllColours(objects.particles, GREEN);
    distributePositionsRandomly(objects.particles, box_dimensions, 1, 1);
    distributeVelocitiesRandomly(objects.particles, 400);

    for (Particle &particle : objects.particles)
    {
        particle.setRadius(7);
    }

    const float amplitude = 1000;
    const float time_period = 120;
    objects.walls[3].setOscillation(box_dimensions.width - amplitude, amplitude, time_period);
}

void Demos::gasInGravity(Objects &objects, BoxDimensions &box_dimensions)
{
    box_dimensions.width = 250;
    objects.particles.resize(800);
    objects.dot_data.dots.resize(500);

    const int g = 100;
    const float e = 0.995;

    setAllColours(objects.particles, {200, 200, 200, 255});

    size_t i = 0;
    for (Particle &particle : objects.particles)
    {
        particle.setAcceleration(0, g);
        particle.setRestitution(e);
        if (i < objects.particles.size() / 2)
        {
            particle.setRadius(2);
            particle.setMass(1);
            particle.setColor(RED);
        }
        else
        {
            particle.setRadius(3);
            particle.setMass(5);
            particle.setColor(BLUE);
        }
        i++;
    }

    distributePositionsRandomly(objects.particles, box_dimensions, 1, 3);
}

void Demos::soundWavesDemo(Objects &objects, BoxDimensions &box_dimensions)
{
    box_dimensions.height = 300;
    objects.particles.resize(1200);
    objects.dot_data.dots.resize(500);
    objects.dot_data.particle_to_follow_index = 1;

    setAllColours(objects.particles, LIGHTGRAY);
    distributePositionsRandomly(objects.particles, box_dimensions, 1, 1);
    distributeVelocitiesRandomly(objects.particles, 20);

    for (Particle &particle : objects.particles)
    {
        particle.setRadius(5);
    }

    const int amplitude = 500;

    for (Particle &particle : objects.particles)
    {
        const float x_position = particle.getPosition()[0];

        if (x_position > box_dimensions.width - 2 * amplitude)
        {
            particle.setColor({255, 141, 155, 255});
        }
    }

    const float time_period = 25;
    objects.walls[3].setOscillation(box_dimensions.width - amplitude, amplitude, time_period);
}

void Demos::orbitsDemo(Objects &objects, BoxDimensions &box_dimensions)
{
    box_dimensions.width = 1800;
    box_dimensions.height = 1800;
    objects.particles.resize(400);

    setAllColours(objects.particles, {200, 200, 200, 255});
    distributeRadiusRandomly(objects.particles, 2, 7);

    objects.particles[0].setPosition(box_dimensions.width / 2, box_dimensions.height / 2);
    objects.particles[0].setRadius(60);
    objects.particles[0].setMass(60 * 60 * 60 * 100);

    for (size_t i = 1; i < objects.particles.size(); i++)
    {
        const float angle = rand() % objects.particles.size(); // rotation so not all at same starting pos.

        const float dist = 150 + rand() % 700;

        const float x_pos = box_dimensions.width / 2 + dist * cos(angle);
        const float y_pos = box_dimensions.height / 2 + dist * sin(angle);

        objects.particles[i].setPosition(x_pos, y_pos);

        const float speed = 1 * sqrt(objects.particles[0].getMass() / dist); // newtons laws for circ orbits + slight reduction

        const float x_vel = -1 * speed * sin(angle);
        const float y_vel = speed * cos(angle);

        objects.particles[i].setVelocity(x_vel, y_vel);
        objects.particles[i].setRestitution(0.15);

        objects.particles[i].setMass(objects.particles[i].getMass() * 10);
    }
}

void Demos::binaryDemo(Objects &objects, BoxDimensions &box_dimensions)
{
    objects.particles.resize(400);

    setAllColours(objects.particles, {0, 0, 0, 255});

    distributePositionsRandomly(objects.particles, box_dimensions, 1, 1);

    const int dist = 250;

    const float large_mass = 10000000;
    const int large_radius = int(cbrt(large_mass / 100));
    objects.particles[0].setPosition(box_dimensions.width / 2, box_dimensions.height / 2);
    objects.particles[0].setRadius(large_radius);
    objects.particles[0].setMass(large_mass);

    const float m0 = objects.particles[0].getMass();
    const float v1 = 60;

    objects.particles[0].setVelocity(0, v1);

    const float small_mass = 4000000;
    const int small_radius = int(cbrt(large_mass / 100));
    objects.particles[1].setPosition(box_dimensions.width / 2 + 2 * 30 + dist, box_dimensions.height / 2);
    objects.particles[1].setRadius(small_radius);
    objects.particles[1].setMass(small_mass);

    const float m1 = objects.particles[1].getMass();
    const float v2 = -1 * m0 / m1 * v1;

    objects.particles[1].setVelocity(0, v2);

    for (size_t i = 2; i < objects.particles.size(); i++)
    {
        const float angle = rand() % objects.particles.size(); // rotation so not all at same starting pos.

        const float dist = 450 + rand() % 1000;

        const float x_pos = box_dimensions.width / 2 + dist * cos(angle);
        const float y_pos = box_dimensions.height / 2 + dist * sin(angle);

        objects.particles[i].setPosition(x_pos, y_pos);

        const float speed = 0.95 * sqrt((objects.particles[0].getMass() + objects.particles[1].getMass()) / dist); // newtons laws for circ orbits + slight reduction

        const float x_vel = speed * sin(angle);
        const float y_vel = -1 * speed * cos(angle);

        objects.particles[i].setVelocity(x_vel, y_vel);
        objects.particles[i].setRestitution(0.8);

        objects.particles[i].setMass(10);
        objects.particles[i].setRadius(2);
        objects.particles[i].setColor({180, 180, 180, 255});
    }
}

void Demos::sunEarthMoonDemo(Objects &objects, BoxDimensions &box_dimensions)
{
    box_dimensions.width = 2000;
    objects.particles.resize(5);
    objects.dot_data.dots.resize(0);

    const int radius_sun = 100;
    const int radius_earth = 10;
    const int radius_moon = 2;
    const int radius_mercury = 8;
    const int radius_mercury_moon = 2;

    objects.particles[0].setRadius(radius_sun);
    objects.particles[1].setRadius(radius_earth);
    objects.particles[2].setRadius(radius_moon);
    objects.particles[3].setRadius(radius_mercury);
    objects.particles[4].setRadius(radius_mercury_moon);

    const int mass_sun = radius_sun * radius_sun * radius_sun * 1;
    const int mass_earth = radius_earth * radius_earth * radius_earth * 10;
    const int mass_moon = radius_moon * radius_moon * radius_moon * 1;
    const int mass_mercury = radius_mercury * radius_mercury * radius_mercury * 10;
    const int mass_mercury_moon = radius_mercury_moon * radius_mercury_moon * radius_mercury_moon * 1;

    objects.particles[0].setMass(mass_sun);
    objects.particles[1].setMass(mass_earth);
    objects.particles[2].setMass(mass_moon);
    objects.particles[3].setMass(mass_mercury);
    objects.particles[4].setMass(mass_mercury_moon);

    objects.particles[0].setPosition(box_dimensions.width / 2, box_dimensions.height / 2);

    const int earth_sun_dist = 875;
    objects.particles[1].setPosition(box_dimensions.width / 2 + earth_sun_dist, box_dimensions.height / 2);
    const float v_earth = sqrt(mass_sun / earth_sun_dist); // newtons laws for circ orbits
    objects.particles[1].setVelocity(0, v_earth);

    const int earth_moon_dist = 15;
    objects.particles[2].setPosition(box_dimensions.width / 2 + earth_sun_dist + earth_moon_dist, box_dimensions.height / 2);
    const float v_moon = v_earth + sqrt(mass_earth / earth_moon_dist); // newtons laws for circ orbits
    objects.particles[2].setVelocity(0, v_moon);

    const int mercury_sun_dist = 500;
    objects.particles[3].setPosition(box_dimensions.width / 2 - mercury_sun_dist, box_dimensions.height / 2);
    const float v_mercury = sqrt(mass_sun / mercury_sun_dist); // newtons laws for circ orbits
    objects.particles[3].setVelocity(0, -v_mercury);

    const int mercury_moon_dist = 20;
    objects.particles[4].setPosition(box_dimensions.width / 2 - mercury_sun_dist - mercury_moon_dist, box_dimensions.height / 2);
    const float v_moon_mercury = v_mercury + sqrt(mass_mercury / mercury_moon_dist); // newtons laws for circ orbits
    objects.particles[4].setVelocity(0, -v_moon_mercury);

    const double v_sun = -1 * (mass_earth * v_earth + mass_moon * v_moon + mass_mercury * v_mercury + mass_mercury_moon * v_moon_mercury) / mass_sun;
    objects.particles[0].setVelocity(0, v_sun);

    objects.particles[0].setColor(GOLD);
    objects.particles[1].setColor(GREEN);
    objects.particles[2].setColor(Color{190, 190, 190, 255});
    objects.particles[3].setColor(RED);
    objects.particles[4].setColor(Color{190, 190, 190, 255});
}

void Demos::lotsOfParticlesDemo(Objects &objects, BoxDimensions &box_dimensions)
{
    objects.particles.resize(250);

    const float e = 0.8;

    setAllColours(objects.particles, {200, 200, 200, 255});
    distributeVelocitiesRandomly(objects.particles, 500);

    distributePositionsRandomly(objects.particles, box_dimensions, 1, 1);
    distributeRadiusRandomly(objects.particles, 15, 50);
    setMassForConstantDensity2D(objects.particles, 500);
    for (Particle &particle : objects.particles)
    {
        particle.setRestitution(e);
    }
}

void Demos::ionLatticeDemo(Objects &objects, BoxDimensions &box_dimensions)
{
    box_dimensions.width = 1200;
    box_dimensions.height = 800;
    objects.particles.resize(800);

    distributePositionsRandomly(objects.particles, box_dimensions, 1, 1);

    const float q = 0.015;

    for (size_t i = 0; i < objects.particles.size(); i++)
    {
        Particle &particle = objects.particles[i];

        if (i < objects.particles.size() / 2)
        {
            particle.setRadius(16);
            particle.setCharge(q);
        }
        else
        {
            particle.setRadius(8);
            particle.setCharge(-q);
        }
        particle.setRestitution(0.6);
    }
}

void Demos::chargeFourIonsDemo(Objects &objects, BoxDimensions &box_dimensions)
{
    objects.particles.resize(250);

    distributePositionsRandomly(objects.particles, box_dimensions, 1, 1);

    for (Particle &particle : objects.particles)
    {
        particle.setRestitution(0.5);

        const float x_position = particle.getPosition()[0];

        if (x_position < (box_dimensions.width / 10))
        {
            particle.setRadius(40);
            particle.setCharge(4);
        }
        else
        {
            particle.setRadius(10);
            particle.setCharge(-1);
        }
        particle.setRestitution(0.5);
    }
}

void Demos::outerPotential(Objects &objects, BoxDimensions &box_dimensions)
{
    box_dimensions.width = 1800;
    box_dimensions.height = 1800;
    objects.particles.resize(500);

    objects.dot_data.particle_to_follow_index = 480;

    distributePositionsRandomly(objects.particles, box_dimensions, 1, 1);
    distributeRadiusRandomly(objects.particles, 9, 10);

    size_t i = 0;
    for (Particle &particle : objects.particles)
    {
        particle.setRestitution(0);
        particle.setCharge(-0.5);

        size_t number_in_each_wall = 50;
        size_t number_in_walls = 4 * number_in_each_wall;

        if (i < number_in_walls / 4)
        {
            particle.setPosition(box_dimensions.width - 5, box_dimensions.height * i / number_in_each_wall);
        }
        else if (i < number_in_walls / 2)
        {
            particle.setPosition(box_dimensions.width * (i - number_in_each_wall) / number_in_each_wall, box_dimensions.height - 5);
        }
        else if (i < 3 * number_in_walls / 4)
        {
            particle.setPosition(5, box_dimensions.height * (i - 2 * number_in_each_wall) / number_in_each_wall);
        }
        else if (i < number_in_walls)
        {
            particle.setPosition(box_dimensions.width * (i - 3 * number_in_each_wall) / number_in_each_wall, 5);
        }

        if (i < number_in_walls)
        {
            particle.setRadius(8);
            particle.setCharge(-50);
            particle.fixParticle();
        }
        i++;
    }
}

void Demos::ionTrapDemo(Objects &objects, BoxDimensions &box_dimensions)
{
    objects.particles.resize(5);

    objects.dot_data.particle_to_follow_index = 4;

    objects.particles[0].setCharge(4);
    objects.particles[0].setRadius(4);
    objects.particles[0].setPosition(box_dimensions.width / 2, box_dimensions.height / 2);
    objects.particles[0].setVelocity(100, 50);

    for (size_t i = 1; i < objects.particles.size(); i++)
    {
        Particle &particle = objects.particles[i];
        particle.setCharge(0.05);
        particle.setRadius(40);
        particle.fixParticle();
    }

    const int dist = 200;
    objects.particles[1].setPosition(box_dimensions.width / 2 + dist, box_dimensions.height / 2);
    objects.particles[2].setPosition(box_dimensions.width / 2, box_dimensions.height / 2 + dist);
    objects.particles[3].setPosition(box_dimensions.width / 2, box_dimensions.height / 2 - dist);
    objects.particles[4].setPosition(box_dimensions.width / 2 - dist, box_dimensions.height / 2);
}

void Demos::allSameChargeDemo(Objects &objects, BoxDimensions &box_dimensions)
{
    box_dimensions.height = 800;
    objects.particles.resize(1000);

    distributePositionsRandomly(objects.particles, box_dimensions, 1, 1);

    for (Particle &particle : objects.particles)
    {
        particle.setRadius(10);
        particle.setCharge(-1);
        particle.setRestitution(0.2);
    }
}

void Demos::rocketDemo(Objects &objects, BoxDimensions &box_dimensions)
{
    objects.particles.resize(1);

    for (Particle &particle : objects.particles)
    {
        particle.setColor(WHITE);
        particle.setMass(5000);
        particle.setRadius(50);
        particle.setPosition(box_dimensions.width / 2, box_dimensions.height / 2);
    }
}

void Demos::rocketOrbitsDemo(Objects &objects, BoxDimensions &box_dimensions)
{

    objects.particles.resize(300);

    setAllColours(objects.particles, {200, 200, 200, 255});
    distributeRadiusRandomly(objects.particles, 2, 10);

    const Vector center = {(float)box_dimensions.width / 2, (float)box_dimensions.height / 2};

    const float big_mass = 60*60*60*150;
    objects.particles[0].setPosition(center);
    objects.particles[0].setRadius(60);
    objects.particles[0].setMass(big_mass);

    const float big_dist = 25000;

    const float speed = sqrt(2*big_mass / big_dist);
    objects.particles[0].setVelocity(0, speed);

    const Vector other_pos = center + Vector{big_dist, 0};

    objects.particles[1].setPosition(other_pos);
    objects.particles[1].setRadius(60);
    objects.particles[1].setMass(big_mass);
    objects.particles[1].setVelocity(0, -speed);

    for (size_t i = 2; i < objects.particles.size() / 2; i++)
    {
        const float angle = rand() % objects.particles.size() / 2; // rotation so not all at same starting pos.

        const float dist = 80 + rand() % 2000;

        const float x_pos = center.getx() + dist * cos(angle);
        const float y_pos = center.gety() + dist * sin(angle);

        objects.particles[i].setPosition(x_pos, y_pos);

        const float speed = 0.95 * sqrt(objects.particles[0].getMass() / dist); // newtons laws for circ orbits + slight reduction

        const float x_vel = -1 * speed * sin(angle);
        const float y_vel = speed * cos(angle);

        objects.particles[i].setVelocity(x_vel, y_vel);
        objects.particles[i].setRestitution(0.15);

        objects.particles[i].setMass(objects.particles[i].getMass());
    }

    for (size_t i = objects.particles.size() / 2; i < objects.particles.size(); i++)
    {
        const float angle = rand() % objects.particles.size() / 2; // rotation so not all at same starting pos.
        const float dist = 200 + rand() % 6000;

        const float x_pos = other_pos.getx() + dist * cos(angle);
        const float y_pos = other_pos.gety() + dist * sin(angle);

        objects.particles[i].setPosition(x_pos, y_pos);

        const float speed = 0.95 * sqrt(objects.particles[0].getMass() / dist); // newtons laws for circ orbits + slight reduction

        const float x_vel = -1 * speed * sin(angle);
        const float y_vel = speed * cos(angle);

        objects.particles[i].setVelocity(x_vel, y_vel);
        objects.particles[i].setRestitution(0.15);

        objects.particles[i].setMass(objects.particles[i].getMass());
    }
}

void Demos::bugFix(Objects &objects, BoxDimensions &box_dimensions)
{
    objects.particles.resize(1);

    for (Particle &particle : objects.particles)
    {
        particle.setColor(WHITE);
        particle.setMass(50000000);
        particle.setRadius(50);
        particle.setPosition(box_dimensions.width / 2, box_dimensions.height / 2);
    }
}

//
// helper functions
//

void Demos::distributePositionsRandomly(std::vector<Particle> &particles, BoxDimensions &box_dimensions, int fill_fraction_x, int fill_fraction_y)
{
    for (Particle &particle : particles)
    {
        const int left_limit = particle.getRadius() + (1 - (float)1 / fill_fraction_x) * box_dimensions.width / 2;
        const int right_limit = box_dimensions.width - particle.getRadius() - (1 - (float)1 / fill_fraction_x) * box_dimensions.width / 2;
        const int width = right_limit - left_limit;

        const int top_limit = particle.getRadius() + (1 - (float)1 / fill_fraction_y) * box_dimensions.height / 2;
        const int bottom_limit = box_dimensions.height - particle.getRadius() - (1 - (float)1 / fill_fraction_y) * box_dimensions.height / 2;
        const int height = bottom_limit - top_limit;

        const float random_x_position = right_limit - rand() % width;
        const float random_y_position = bottom_limit - rand() % height;

        particle.setPosition(random_x_position, random_y_position);
    }
}

void Demos::distributeVelocitiesRandomly(std::vector<Particle> &particles, int max_velocity)
{
    if (max_velocity > 0)
    {
        for (Particle &particle : particles)
        {
            const float random_x_velocity = rand() % (max_velocity * 2) - max_velocity;
            const float random_y_velocity = rand() % (max_velocity * 2) - max_velocity;

            particle.setVelocity(random_x_velocity, random_y_velocity);
        }
    }
}

void Demos::distributeRadiusRandomly(std::vector<Particle> &particles, int min_radius, int max_radius)
{
    for (Particle &particle : particles)
    {
        const int radius = rand() % (max_radius - min_radius) + min_radius;
        particle.setRadius(radius);
        setMassForConstantDensity3D(particles, 1);
    }
}

void Demos::setMassForConstantDensity3D(std::vector<Particle> &particles, const int density)
{
    for (Particle &particle : particles)
    {
        const int radius = particle.getRadius();
        const int mass = density * radius * radius * radius;
        particle.setMass(mass);
    }
}

void Demos::setMassForConstantDensity2D(std::vector<Particle> &particles, const int density)
{
    for (Particle &particle : particles)
    {
        const int radius = particle.getRadius();
        const int mass = density * radius * radius;
        particle.setMass(mass);
    }
}

void Demos::setAllColours(std::vector<Particle> &particles, Color color)
{
    for (Particle &particle : particles)
    {
        particle.setColor(color);
    }
}

void Demos::initialiseWalls(std::vector<Wall> &walls, BoxDimensions &box_dimensions)
{
    const int border = 10;
    walls[0].setupWall(x, min, 0 + border, box_dimensions.width);
    walls[1].setupWall(x, max, box_dimensions.height - border, box_dimensions.width);
    walls[2].setupWall(y, min, 0 + border, box_dimensions.height);
    walls[3].setupWall(y, max, box_dimensions.width - border, box_dimensions.height);
}

void Demos::setupRocket(Rocket &rocket)
{
    rocketEngines(rocket);
    rocketMomentOfInertia(rocket);
}

void Demos::rocketMomentOfInertia(Rocket &rocket)
{
    const float m = rocket.getMass();

    const float w = rocket.getWidth();
    const float h = rocket.getHeight();

    const float less_rotation_factor = 5;

    const float I = m * (w * w + h * h) / 12;

    rocket.setI(less_rotation_factor * I);
}

void Demos::rocketEngines(Rocket &rocket)
{
    const float half_w = rocket.getWidth() / 2;
    const float half_h = rocket.getHeight() / 2;

    const float base_force_mag = 25;

    rocket.engines[1].base_force.F = base_force_mag * Vector{-1, 0};
    rocket.engines[1].base_force.b = {-half_w, -half_h};

    rocket.engines[2].base_force.F = base_force_mag * Vector{0, -1};
    rocket.engines[2].base_force.b = {0, -half_h};

    rocket.engines[3].base_force.F = base_force_mag * Vector{1, 0};
    rocket.engines[3].base_force.b = {half_w, -half_h};

    rocket.engines[4].base_force.F = base_force_mag * Vector{-1, 0};
    rocket.engines[4].base_force.b = {-half_w, 0};

    rocket.engines[6].base_force.F = base_force_mag * Vector{1, 0};
    rocket.engines[6].base_force.b = {half_w, 0};

    rocket.engines[7].base_force.F = base_force_mag * Vector{-1, 0};
    rocket.engines[7].base_force.b = {-half_w, half_h};

    rocket.engines[8].base_force.F = base_force_mag * Vector{0, 1};
    rocket.engines[8].base_force.b = {0, half_h};

    rocket.engines[9].base_force.F = base_force_mag * Vector{1, 0};
    rocket.engines[9].base_force.b = {half_w, half_h};

    for (Engine &engine : rocket.engines)
    {
        engine.initial_display_line[0] = engine.base_force.b;
        engine.initial_display_line[1] = engine.base_force.b + engine.base_force.F;

        engine.display_line[0] = engine.initial_display_line[0];
        engine.display_line[1] = engine.initial_display_line[1];
    }
}
