#include "../src/calculators/ReferenceFrameCalculator.h"

#include <gtest/gtest.h>

TEST(ReferenceFrameCalculator, rocket_gets_centered_and_oriented_upwards)
{
    // Given
    const BoxDimensions box_dimensions(200, 300);

    Objects objects;
    objects.rocket.setPosition(20, 15);
    objects.rocket.setVelocity(1, 0);
    objects.rocket.setAcceleration(1, 1);
    objects.rocket.setAngle(-PI / 2);

    objects.particles.resize(1);

    ReferenceFrameCalculator reference_frame_calculator(box_dimensions);

    // When
    reference_frame_calculator.changeToRocketFrame(objects);

    // Then
    RotationalParticle expected_master_particle;
    expected_master_particle.setPosition(box_dimensions.width / 2, box_dimensions.height / 2);
    expected_master_particle.setVelocity(0, 1);
    expected_master_particle.setAcceleration(-1, 1);
    expected_master_particle.setAngle(0);

    ASSERT_EQ(expected_master_particle, objects.rocket);
}

TEST(ReferenceFrameCalculator, particles_get_shifted_and_rotated_by_same_amount_as_rocket)
{
    // Given
    const BoxDimensions box_dimensions(200, 300);

    Objects objects;
    objects.rocket.setPosition(20, 15);
    objects.rocket.setAngle(-PI / 2);

    objects.particles.resize(1);

    objects.particles[0].setPosition(10, 20);
    objects.particles[0].setVelocity(2, 1);
    objects.particles[0].setAcceleration(-1, 3);

    ReferenceFrameCalculator reference_frame_calculator(box_dimensions);

    // When
    reference_frame_calculator.changeToRocketFrame(objects);

    // Then
    LinearParticle expected_particle;
    expected_particle.setPosition(95, 140);
    expected_particle.setVelocity(-1, 2);
    expected_particle.setAcceleration(-3, -1);

    ASSERT_EQ(expected_particle, objects.particles[0]);
}

TEST(ReferenceFrameCalculator, dot_get_shifted_and_rotated_by_same_amount_as_rocket)
{
    // Given
    const BoxDimensions box_dimensions(200, 300);

    Objects objects;
    objects.rocket.setPosition(20, 15);
    objects.rocket.setAngle(-PI / 2);

    objects.particles.resize(1);

    objects.dot_data.dots.resize(1);
    objects.dot_data.dots[0].setPosition(Vector{10, 20});

    ReferenceFrameCalculator reference_frame_calculator(box_dimensions);

    // When
    reference_frame_calculator.changeToRocketFrame(objects);

    // Then

    const Vector expected_dot_position = {95, 140};

    objects.dot_data.dots.resize(1);
    objects.dot_data.dots[0].setPosition(Vector{10, 20});
}

TEST(ReferenceFrameCalculator, change_to_universe_frame_undoes_changes_rocket)
{
    // Given
    const BoxDimensions box_dimensions(200, 300);

    Objects objects;
    objects.rocket.setPosition(20, 15);
    objects.rocket.setVelocity(1, 0);
    objects.rocket.setAcceleration(1, 1);

    objects.particles.resize(1);

    ReferenceFrameCalculator reference_frame_calculator(box_dimensions);

    reference_frame_calculator.changeToRocketFrame(objects);

    // When
    reference_frame_calculator.changeToUniverseFrame(objects);

    // Then
    LinearParticle expected_master_particle;
    expected_master_particle.setPosition(20, 15);
    expected_master_particle.setVelocity(1, 0);
    expected_master_particle.setAcceleration(1, 1);

    ASSERT_EQ(expected_master_particle, objects.rocket);
}

TEST(ReferenceFrameCalculator, change_to_universe_frame_undoes_changes_particles)
{
    // Given
    const BoxDimensions box_dimensions(200, 300);

    Objects objects;
    objects.rocket.setPosition(20, 15);
    objects.rocket.setVelocity(1, 0);
    objects.rocket.setAcceleration(1, 1);

    objects.particles.resize(1);

    objects.particles[0].setPosition(10, 20);
    objects.particles[0].setVelocity(2, 1);
    objects.particles[0].setAcceleration(-1, 3);

    ReferenceFrameCalculator reference_frame_calculator(box_dimensions);

    reference_frame_calculator.changeToRocketFrame(objects);

    // When
    reference_frame_calculator.changeToUniverseFrame(objects);

    // Then
    LinearParticle expected_particle;
    expected_particle.setPosition(10, 20);
    expected_particle.setVelocity(2, 1);
    expected_particle.setAcceleration(-1, 3);

    ASSERT_EQ(expected_particle, objects.particles[0]);
}

TEST(ReferenceFrameCalculator, change_to_universe_frame_undoes_changes_dots)
{
    // Given
    const BoxDimensions box_dimensions(200, 300);

    Objects objects;
    objects.rocket.setPosition(20, 15);
    objects.rocket.setVelocity(1, 0);
    objects.rocket.setAcceleration(1, 1);

    objects.particles.resize(1);

    objects.dot_data.dots.resize(1);
    objects.dot_data.dots[0].setPosition(Vector{10, 20});

    ReferenceFrameCalculator reference_frame_calculator(box_dimensions);

    reference_frame_calculator.changeToRocketFrame(objects);

    // When
    reference_frame_calculator.changeToUniverseFrame(objects);

    // Then
    const Vector expected_dot_position = {10, 20};

    ASSERT_EQ(expected_dot_position, objects.dot_data.dots[0].getPosition());
}

TEST(ReferenceFrameCalculator, change_to_rocket_frame_updates_preserved_when_changing_back_rocket)
{
    // Given
    const BoxDimensions box_dimensions(200, 300);

    Objects objects;
    objects.rocket.setPosition(20, 15);
    objects.rocket.setVelocity(1, 0);
    objects.rocket.setAcceleration(1, 1);
    objects.rocket.setAngle(-PI / 2);

    objects.particles.resize(1);

    ReferenceFrameCalculator reference_frame_calculator(box_dimensions);

    reference_frame_calculator.changeToRocketFrame(objects);

    objects.rocket.setPosition(box_dimensions.width / 2 + 1, box_dimensions.height / 2 + 1);
    objects.rocket.setVelocity(1, 0);

    reference_frame_calculator.changeToRocketFrame(objects);

    // When
    reference_frame_calculator.changeToUniverseFrame(objects);

    // Then
    RotationalParticle expected_master_particle;
    expected_master_particle.setPosition(21, 14);
    expected_master_particle.setVelocity(0, -1);
    expected_master_particle.setAcceleration(1, 1);
    expected_master_particle.setAngle(-PI / 2);

    ASSERT_EQ(expected_master_particle, objects.rocket);
}

TEST(ReferenceFrameCalculator, change_to_rocket_frame_updates_preserved_when_changing_back_particle)
{
    // Given
    const BoxDimensions box_dimensions(200, 3000);

    Objects objects;
    objects.rocket.setPosition(20, 150);
    objects.rocket.setAngle(-PI / 2);

    objects.particles.resize(1);

    objects.particles[0].setPosition(10, 200);
    objects.particles[0].setVelocity(2, 1);
    objects.particles[0].setAcceleration(-1, 3);

    ReferenceFrameCalculator reference_frame_calculator(box_dimensions);

    // lots of random updates
    reference_frame_calculator.changeToRocketFrame(objects);

    objects.rocket.setPosition(200, 300);
    objects.rocket.setVelocity(1, 20);

    reference_frame_calculator.changeToRocketFrame(objects);

    objects.rocket.setPosition(150, 400);
    objects.rocket.setVelocity(-31, 20);

    reference_frame_calculator.changeToRocketFrame(objects);

    objects.rocket.setPosition(50, 600);
    objects.rocket.setVelocity(60, -20);

    reference_frame_calculator.changeToRocketFrame(objects);

    objects.rocket.setPosition(10, 800);
    objects.rocket.setVelocity(-70, -20);

    reference_frame_calculator.changeToRocketFrame(objects);

    // When
    reference_frame_calculator.changeToUniverseFrame(objects);

    // Then
    LinearParticle expected_particle;
    expected_particle.setPosition(10, 200);
    expected_particle.setVelocity(2, 1);
    expected_particle.setAcceleration(-1, 3);

    ASSERT_EQ(expected_particle, objects.particles[0]);
}

TEST(ReferenceFrameCalculator, change_to_rocket_frame_updates_preserved_when_changing_back_particle_at_center)
{
    // Given
    const BoxDimensions box_dimensions(200, 3000);

    Objects objects;
    objects.rocket.setPosition(20, 150);
    objects.rocket.setAngle(-PI / 2);

    objects.particles.resize(1);

    objects.particles[0].setPosition(box_dimensions.width / 2, box_dimensions.height / 2);
    objects.particles[0].setVelocity(2, 1);
    objects.particles[0].setAcceleration(-1, 3);

    ReferenceFrameCalculator reference_frame_calculator(box_dimensions);

    // lots of random updates
    reference_frame_calculator.changeToRocketFrame(objects);

    objects.rocket.setPosition(200, 300);
    objects.rocket.setVelocity(1, 20);

    reference_frame_calculator.changeToRocketFrame(objects);

    objects.rocket.setPosition(150, 400);
    objects.rocket.setVelocity(-31, 20);

    reference_frame_calculator.changeToRocketFrame(objects);

    objects.rocket.setPosition(50, 600);
    objects.rocket.setVelocity(60, -20);

    reference_frame_calculator.changeToRocketFrame(objects);

    objects.rocket.setPosition(10, 800);
    objects.rocket.setVelocity(-70, -20);

    reference_frame_calculator.changeToRocketFrame(objects);

    // When
    reference_frame_calculator.changeToUniverseFrame(objects);

    // Then
    LinearParticle expected_particle;
    expected_particle.setPosition(box_dimensions.width / 2, box_dimensions.height / 2);
    expected_particle.setVelocity(2, 1);
    expected_particle.setAcceleration(-1, 3);

    ASSERT_EQ(expected_particle, objects.particles[0]);
}

TEST(ReferenceFrameCalculator, change_to_rocket_frame_updates_preserved_when_changing_back_dot)
{
    // Given
    const BoxDimensions box_dimensions(200, 300);

    Objects objects;
    objects.rocket.setPosition(20, 15);
    objects.rocket.setAngle(-PI / 2);

    objects.particles.resize(1);

    objects.dot_data.dots.resize(1);
    objects.dot_data.dots[0].setPosition(Vector{10, 20});

    ReferenceFrameCalculator reference_frame_calculator(box_dimensions);

    // lots of random updates
    reference_frame_calculator.changeToRocketFrame(objects);

    objects.rocket.setPosition(200, 300);
    objects.rocket.setVelocity(1, 20);

    reference_frame_calculator.changeToRocketFrame(objects);

    objects.rocket.setPosition(250, 400);
    objects.rocket.setVelocity(-31, 20);

    reference_frame_calculator.changeToRocketFrame(objects);

    objects.rocket.setPosition(250, 400);
    objects.rocket.setVelocity(60, -20);

    reference_frame_calculator.changeToRocketFrame(objects);

    objects.rocket.setPosition(250, 400);
    objects.rocket.setVelocity(-70, -20);

    reference_frame_calculator.changeToRocketFrame(objects);

    // When
    reference_frame_calculator.changeToUniverseFrame(objects);

    // Then
    const Vector expected_dot_position = {10, 20};

    ASSERT_EQ(expected_dot_position, objects.dot_data.dots[0].getPosition());
}