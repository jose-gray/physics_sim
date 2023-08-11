#include "../src/calculators/RocketCalculator.h"

#include <gtest/gtest.h>

class rocketCalculatorFixture : public ::testing::Test
{
protected:
    Rocket rocket;
    LinearParticle particle;
    RocketCalculator rocket_calculator;
};

void setupRocketEngines(Rocket &rocket)
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

    for(Engine &engine : rocket.engines)
    {
        engine.initial_display_line[0] = engine.base_force.b;
        engine.initial_display_line[1] = engine.base_force.b + engine.base_force.F;

        engine.display_line[0] = engine.initial_display_line[0];
        engine.display_line[1] = engine.initial_display_line[1];
    }
}

TEST_F(rocketCalculatorFixture, vertices)
{
    // Given
    rocket.setDisplayPosition(100, 100);

    // When
    rocket_calculator.updateRocket(rocket, particle);

    // Then
    const std::array<Vector, 4> vertices = rocket.getVertices();

    const std::array<Vector, 4> expected_vertices =
        {
            Vector{110, 140},
            Vector{90, 140},
            Vector{90, 60},
            Vector{110, 60}};

    ASSERT_EQ(expected_vertices, vertices);
}

TEST_F(rocketCalculatorFixture, rocket_with_angle_aligns_towards_angle)
{
    // Given
    rocket.setDisplayPosition(100, 100);
    rocket.setAngle(PI / 2);

    // When
    rocket_calculator.updateRocket(rocket, particle);

    // Then
    const std::array<Vector, 4> vertices = rocket.getVertices();

    const std::array<Vector, 4> expected_vertices =
        {
            Vector{60, 110},
            Vector{60, 90},
            Vector{140, 90},
            Vector{140, 110}};

    ASSERT_EQ(expected_vertices, vertices);
}

TEST_F(rocketCalculatorFixture, return_rocket_to_home_universe_frame)
{
    // Given
    rocket.setPosition(100, 100);
    rocket.setVelocity(5, 3);
    rocket.setAcceleration(100, 200);

    rocket.setAngle(25);
    rocket.setVelocity_Angular(1);
    rocket.setAcceleration_Angular(1);

    // When
    rocket_calculator.returnRocketHome(rocket);

    // Then
    RotationalParticle expected_rocket;
    expected_rocket.setPosition(0, 0);
    expected_rocket.setVelocity(0, 0);
    expected_rocket.setAcceleration(0, 0);
    expected_rocket.setAngle(0);
    expected_rocket.setVelocity_Angular(0);
    expected_rocket.setAcceleration_Angular(0);

    ASSERT_EQ(expected_rocket, rocket);
}

TEST_F(rocketCalculatorFixture, rocket_acceleration_force_added_no_angle)
{
    // Given
    rocket.setPosition(100, 100);

    Force engine_force;
    engine_force.F = {1, 1};
    engine_force.b = {2, 2};
    rocket.engines[0].base_force = engine_force;

    rocket.engines[0].is_on = true;

    // When
    rocket_calculator.updateRocket(rocket, particle);

    // Then
    Force force;
    force.F = {1, 1};
    force.b = {102, 102};
    const std::vector<Force> expected_force = {force};

    const std::vector<Force> F = rocket.getForces();

    ASSERT_EQ(expected_force, F);
}

TEST_F(rocketCalculatorFixture, rocket_acceleration_force_added_angle)
{
    // Given
    rocket.setPosition(100, 100);
    rocket.setAngle(PI / 2);

    Force engine_force;
    engine_force.F = {1, 2};
    engine_force.b = {2, 3};
    rocket.engines[0].base_force = engine_force;

    rocket.engines[0].is_on = true;

    // When
    rocket_calculator.updateRocket(rocket, particle);

    // Then
    Force force;
    force.F = {-2, 1};
    force.b = {97, 102};
    const std::vector<Force> expected_force = {force};

    const std::vector<Force> F = rocket.getForces();

    ASSERT_EQ(expected_force, F);
}

TEST_F(rocketCalculatorFixture, rocket_acceleration_force_added_boost)
{
    // Given
    rocket.setPosition(100, 100);
    rocket.setAngle(PI / 2);

    Force engine_force;
    engine_force.F = {1, 2};
    engine_force.b = {2, 3};
    rocket.engines[0].base_force = engine_force;

    rocket.engines[0].is_on = true;
    rocket.boost_mode = true;

    // When
    rocket_calculator.updateRocket(rocket, particle);

    // Then
    Force force;
    force.F = {-10, 5};
    force.b = {97, 102};
    const std::vector<Force> expected_force = {force};

    const std::vector<Force> F = rocket.getForces();

    ASSERT_EQ(expected_force, F);
}

TEST_F(rocketCalculatorFixture, rocket_acceleration_display_line_rotated)
{
    // Given
    rocket.setPosition(100, 100);
    rocket.setAngle(PI / 2);

    rocket.engines[0].is_on = true;
    rocket.engines[0].initial_display_line = {Vector{1, 1}, Vector{2, 1}};

    // When
    rocket_calculator.updateRocket(rocket, particle);

    // Then
    const std::array<Vector, 2> expected_line = {Vector{99, 101}, Vector{99, 102}};

    const std::array<Vector, 2> actual_line = rocket.engines[0].display_line;

    ASSERT_EQ(expected_line, actual_line);
}

TEST_F(rocketCalculatorFixture, rocket_acceleration_display_line_longer_in_boost_mode)
{
    // Given
    rocket.setPosition(100, 100);
    rocket.setAngle(PI / 2);

    rocket.engines[0].is_on = true;
    rocket.engines[0].initial_display_line = {Vector{1, 1}, Vector{2, 1}};

    rocket.boost_mode = true;

    // When
    rocket_calculator.updateRocket(rocket, particle);

    // Then
    const std::array<Vector, 2> expected_line = {Vector{99, 101}, Vector{99, 103.236}};

    const std::array<Vector, 2> actual_line = rocket.engines[0].display_line;

    ASSERT_EQ(expected_line, actual_line);
}

TEST_F(rocketCalculatorFixture, rocket_com_set_to_position)
{
    // Given
    const Vector position = {100, 100};
    rocket.setPosition(position);

    // When
    rocket_calculator.updateRocket(rocket, particle);

    // Then
    const Vector actual_com = rocket.getCom();

    ASSERT_EQ(position, actual_com);
}

TEST_F(rocketCalculatorFixture, rocket_stabiliser_with_no_rotational_velocity_adds_no_forces)
{
    // Given
    rocket.stabiliserOn = true;
    setupRocketEngines(rocket);

    // When
    rocket_calculator.updateRocket(rocket, particle);

    // Then
    const std::vector<Force> expected_force = {};

    const std::vector<Force> F = rocket.getForces();

    ASSERT_EQ(expected_force, F);
}

TEST_F(rocketCalculatorFixture, rocket_stabiliser_with_rotational_velocity_less_than_hundrenth_adds_no_forces)
{
    // Given
    rocket.stabiliserOn = true;
    rocket.setVelocity_Angular(0.01);
    setupRocketEngines(rocket);

    // When
    rocket_calculator.updateRocket(rocket, particle);

    // Then
    const std::vector<Force> expected_force = {};

    const std::vector<Force> F = rocket.getForces();

    ASSERT_EQ(expected_force, F);
}

TEST_F(rocketCalculatorFixture, rocket_stabiliser_with_pos_rotational_velocity_turns_on_engines_both_and_corners)
{
    // Given
    rocket.stabiliserOn = true;
    rocket.setVelocity_Angular(1);
    setupRocketEngines(rocket);

    // When
    rocket_calculator.updateRocket(rocket, particle);

    // Then
    Force engine_force_9;
    engine_force_9.F = {25, 0};
    engine_force_9.b = {10, 40};

    Force engine_force_1;
    engine_force_1.F = {-25, 0};
    engine_force_1.b = {-10, -40};

    const std::vector<Force> expected_force = {engine_force_1, engine_force_9};

    const std::vector<Force> F = rocket.getForces();

    ASSERT_EQ(expected_force, F);
}

TEST_F(rocketCalculatorFixture, rocket_stabiliser_with_pos_rotational_velocity_turns_on_engines_both_and_corners_more_force_when_faster)
{
    // Given
    rocket.stabiliserOn = true;
    rocket.setVelocity_Angular(2);
    setupRocketEngines(rocket);

    // When
    rocket_calculator.updateRocket(rocket, particle);

    // Then
    Force engine_force_9;
    engine_force_9.F = {50, 0};
    engine_force_9.b = {10, 40};

    Force engine_force_1;
    engine_force_1.F = {-50, 0};
    engine_force_1.b = {-10, -40};

    const std::vector<Force> expected_force = {engine_force_1, engine_force_9};

    const std::vector<Force> F = rocket.getForces();

    ASSERT_EQ(expected_force, F);
}

TEST_F(rocketCalculatorFixture, rocket_stabiliser_with_negative_rotational_velocity_turns_on_engines_both_and_corners)
{
    // Given
    rocket.stabiliserOn = true;
    rocket.setVelocity_Angular(-1);
    setupRocketEngines(rocket);

    // When
    rocket_calculator.updateRocket(rocket, particle);

    // Then
    Force engine_force_7;
    engine_force_7.F = {-25, 0};
    engine_force_7.b = {-10, 40};

    Force engine_force_3;
    engine_force_3.F = {25, 0};
    engine_force_3.b = {10, -40};

    const std::vector<Force> expected_force = {engine_force_3, engine_force_7};

    const std::vector<Force> F = rocket.getForces();

    ASSERT_EQ(expected_force, F);
}

TEST_F(rocketCalculatorFixture, rocket_straightner_with_no_rotational_velocity_or_position_adds_no_forces)
{
    // Given
    rocket.straightnerOn = true;
    rocket.setAngle(0);
    rocket.setVelocity({0, 1});
    setupRocketEngines(rocket);

    // When
    rocket_calculator.updateRocket(rocket, particle);

    // Then
    const std::vector<Force> expected_force = {};

    const std::vector<Force> F = rocket.getForces();

    ASSERT_EQ(expected_force, F);
}

TEST_F(rocketCalculatorFixture, rocket_straightner_with_rotational_velocity_and_no_position_adds_forces)
{
    // Given
    rocket.straightnerOn = true;
    rocket.setAngle(PI/2);
    rocket.setVelocity({0, 1});
    rocket.setVelocity_Angular(1);
    setupRocketEngines(rocket);

    // When
    rocket_calculator.updateRocket(rocket, particle);

    // Then
    Force engine_force_7;
    engine_force_7.F = {0, 64.2699};
    engine_force_7.b = {-40, 10};

    Force engine_force_3;
    engine_force_3.F = {0, -64.2699};
    engine_force_3.b = {40, -10};

    const std::vector<Force> expected_force = {engine_force_3, engine_force_7};

    const std::vector<Force> F = rocket.getForces();

    ASSERT_EQ(expected_force, F);
}

TEST_F(rocketCalculatorFixture, rocket_straightner_with_no_rotational_velocity_and_angle_adds_forces)
{
    // Given
    rocket.straightnerOn = true;
    rocket.setAngle(PI);
    rocket.setVelocity({0, 1});
    setupRocketEngines(rocket);

    // When
    rocket_calculator.updateRocket(rocket, particle);

    // Then
    Force engine_force_9;
    engine_force_9.F = {-78.5398, 0};
    engine_force_9.b = {-10, -40};

    Force engine_force_1;
    engine_force_1.F = {78.5398, 0};
    engine_force_1.b = {10, 40};

    const std::vector<Force> expected_force = {engine_force_1, engine_force_9};

    const std::vector<Force> F = rocket.getForces();

    ASSERT_EQ(expected_force, F);
}
