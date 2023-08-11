#include <gtest/gtest.h>

#include <math.h>

#include "../src/calculators/WallCollisionsCalculator.h"
#include "../src/objects/Particle.h"

TEST(WallCollisionsCalculator, getTemperature)
{
    // setup
    std::vector<Particle> particles;
    particles.resize(5);

    for (Particle &particle : particles)
    {
        particle.setMass(2);
    }
    // given
    particles[0].setVelocity(1, 0);
    particles[1].setVelocity(0, 1);
    particles[2].setVelocity(3, 4);
    particles[3].setVelocity(-4, -3);
    particles[4].setVelocity(20, -21);

    WallCollisionsCalculator wall_collisions_calculator;

    // when
    const float actual_temperature = wall_collisions_calculator.getTemperature(particles);

    // then
    const float expected_temperature = 0.1786;

    ASSERT_EQ(expected_temperature, actual_temperature);
}

TEST(WallCollisionsCalculator, unintiliased_particles_temperature_is_zero)
{
    // setup
    std::vector<Particle> particles;
    particles.resize(5);

    // given
    WallCollisionsCalculator wall_collisions_calculator;

    // when
    const float actual_temperature = wall_collisions_calculator.getTemperature(particles);

    // then
    const float expected_temperature = 0;

    ASSERT_EQ(expected_temperature, actual_temperature);
}

TEST(WallCollisionsCalculator, simple_bounce_off_vertical_min_wall)
{
    // setup
    std::vector<Particle> particles;
    particles.resize(1);

    std::vector<Wall> walls;
    walls.resize(4);

    // given
    particles[0].setPosition(5, 10); // overlap of 5
    particles[0].setVelocity(-10, 0);
    particles[0].setRadius(10);

    walls[0].setupWall(y, min, 0, 100);

    WallCollisionsCalculator wall_collisions_calculator;

    // when
    wall_collisions_calculator.updateParticles(particles, walls);

    // then
    const Vector expected_new_position = {15, 10};
    const Vector actual_new_position = particles[0].getPosition();

    ASSERT_EQ(expected_new_position, actual_new_position);

    const Vector expected_new_velocity = {10, 0};
    const Vector actual_new_velocity = particles[0].getVelocity();

    ASSERT_EQ(expected_new_velocity, actual_new_velocity);
}

TEST(WallCollisionsCalculator, simple_bounce_off_vertical_max_wall)
{
    // setup
    std::vector<Particle> particles;
    particles.resize(1);

    std::vector<Wall> walls;
    walls.resize(4);

    // given
    particles[0].setPosition(45, 10); // overlap of 5
    particles[0].setVelocity(10, 0);
    particles[0].setRadius(10);

    walls[0].setupWall(y, max, 50, 100);

    WallCollisionsCalculator wall_collisions_calculator;

    // when
    wall_collisions_calculator.updateParticles(particles, walls);

    // then
    const Vector expected_new_position = {35, 10};
    const Vector actual_new_position = particles[0].getPosition();

    ASSERT_EQ(expected_new_position, actual_new_position);

    const Vector expected_new_velocity = {-10, 0};
    const Vector actual_new_velocity = particles[0].getVelocity();

    ASSERT_EQ(expected_new_velocity, actual_new_velocity);
}

TEST(WallCollisionsCalculator, simple_bounce_off_horizontal_min_wall)
{
    // setup
    std::vector<Particle> particles;
    particles.resize(1);

    std::vector<Wall> walls;
    walls.resize(4);

    // given
    particles[0].setPosition(50, 5); // overlap of 5
    particles[0].setVelocity(0, -10);
    particles[0].setRadius(10);

    walls[0].setupWall(x, min, 0, 100);

    WallCollisionsCalculator wall_collisions_calculator;

    // when
    wall_collisions_calculator.updateParticles(particles, walls);

    // then
    const Vector expected_new_position = {50, 15};
    const Vector actual_new_position = particles[0].getPosition();

    ASSERT_EQ(expected_new_position, actual_new_position);

    const Vector expected_new_velocity = {0, 10};
    const Vector actual_new_velocity = particles[0].getVelocity();

    ASSERT_EQ(expected_new_velocity, actual_new_velocity);
}

TEST(WallCollisionsCalculator, simple_bounce_off_horizontal_max_wall)
{
    // setup
    std::vector<Particle> particles;
    particles.resize(1);

    std::vector<Wall> walls;
    walls.resize(4);

    // given
    particles[0].setPosition(50, 45); // overlap of 5
    particles[0].setVelocity(0, 10);
    particles[0].setRadius(10);

    walls[0].setupWall(x, max, 50, 100);

    WallCollisionsCalculator wall_collisions_calculator;

    // when
    wall_collisions_calculator.updateParticles(particles, walls);

    // then
    const Vector expected_new_position = {50, 35};
    const Vector actual_new_position = particles[0].getPosition();

    ASSERT_EQ(expected_new_position, actual_new_position);

    const Vector expected_new_velocity = {0, -10};
    const Vector actual_new_velocity = particles[0].getVelocity();

    ASSERT_EQ(expected_new_velocity, actual_new_velocity);
}

TEST(WallCollisionsCalculator, moving_wall)
{
    // setup
    std::vector<Particle> particles;
    particles.resize(1);

    std::vector<Wall> walls;
    walls.resize(4);

    // given
    particles[0].setPosition(5, 10); // overlap of 5
    particles[0].setVelocity(-10, 0);
    particles[0].setRadius(10);

    walls[0].setupWall(y, min, 0, 100);

    walls[0].setVelocity(5);

    WallCollisionsCalculator wall_collisions_calculator;

    // when
    wall_collisions_calculator.updateParticles(particles, walls);

    // then
    const Vector expected_new_position = {15, 10};
    const Vector actual_new_position = particles[0].getPosition();

    ASSERT_EQ(expected_new_position, actual_new_position);

    const Vector expected_new_velocity = {15, 0};
    const Vector actual_new_velocity = particles[0].getVelocity();

    ASSERT_EQ(expected_new_velocity, actual_new_velocity);
}

TEST(WallCollisionsCalculator, restitution)
{
    // setup
    std::vector<Particle> particles;
    particles.resize(1);

    std::vector<Wall> walls;
    walls.resize(4);

    // given
    particles[0].setPosition(5, 10); // overlap of 5
    particles[0].setVelocity(-10, 0);
    particles[0].setRadius(10);
    particles[0].setRestitution(0.5);

    walls[0].setupWall(y, min, 0, 100);

    WallCollisionsCalculator wall_collisions_calculator;

    // when
    wall_collisions_calculator.updateParticles(particles, walls);

    // then
    const Vector expected_new_position = {15, 10};
    const Vector actual_new_position = particles[0].getPosition();

    ASSERT_EQ(expected_new_position, actual_new_position);

    const Vector expected_new_velocity = {5, 0};
    const Vector actual_new_velocity = particles[0].getVelocity();

    ASSERT_EQ(expected_new_velocity, actual_new_velocity);
}
