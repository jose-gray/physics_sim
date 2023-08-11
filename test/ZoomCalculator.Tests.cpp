#include <gtest/gtest.h>

#include "../src/calculators/ZoomCalculator.h"

class ZoomCalculatorFixture : public ::testing::Test
{
protected:
    const Vector center = {100, 100};

    ZoomCalculator zoom_calculator{center};

    Objects objects;

    Particle expected_particle;
};

void setupZoomCalculatorObjects(Objects &objects, const Vector center, Particle &expected_particle)
{
    objects.particles.resize(1);
    objects.particles[0].setRadius(10);

    const Vector displacement_from_center = {10, 20};
    const Vector position = center + displacement_from_center;

    objects.particles[0].setPosition(position);

    expected_particle = objects.particles[0];

    objects.dot_data.dots.resize(1);

    objects.dot_data.dots[0].setPosition(position);

    objects.rocket.setPosition(position);
}

TEST_F(ZoomCalculatorFixture, zoom_in_makes_display_radius_bigger_and_display_position_further_from_center)
{
    // Given
    setupZoomCalculatorObjects(objects, center, expected_particle);

    // When
    zoom_calculator.zoomIn(objects);

    // Then
    expected_particle.setDisplayRadius(20);
    const Vector expected_displacement_from_center = {20, 40};
    expected_particle.setDisplayPosition(expected_displacement_from_center + center);

    ASSERT_EQ(expected_particle, objects.particles[0]);
}

TEST_F(ZoomCalculatorFixture, zoom_out_makes_display_radius_smaller_and_display_position_closer_to_center)
{
    // Given
    setupZoomCalculatorObjects(objects, center, expected_particle);

    // When
    zoom_calculator.zoomOut(objects);

    // Then
    expected_particle.setDisplayRadius(5);
    const Vector expected_displacement_from_center = {5, 10};
    expected_particle.setDisplayPosition(expected_displacement_from_center + center);

    ASSERT_EQ(expected_particle, objects.particles[0]);
}

TEST_F(ZoomCalculatorFixture, no_zoom_sets_display_to_same_as_actual)
{
    // Given
    setupZoomCalculatorObjects(objects, center, expected_particle);

    // When
    zoom_calculator.noZoom(objects);

    // Then
    expected_particle.setDisplayRadius(10);
    const Vector expected_displacement_from_center = {10, 20};
    expected_particle.setDisplayPosition(expected_displacement_from_center + center);

    ASSERT_EQ(expected_particle, objects.particles[0]);
}

TEST_F(ZoomCalculatorFixture, zoom_in_then_out_sets_display_to_same_as_actual)
{
    // Given
    setupZoomCalculatorObjects(objects, center, expected_particle);

    // When
    zoom_calculator.zoomIn(objects);
    zoom_calculator.zoomOut(objects);

    // Then
    expected_particle.setDisplayRadius(10);
    const Vector expected_displacement_from_center = {10, 20};
    expected_particle.setDisplayPosition(expected_displacement_from_center + center);

    ASSERT_EQ(expected_particle, objects.particles[0]);
}

TEST_F(ZoomCalculatorFixture, zoom_in_makes_dots_display_position_further_from_center)
{
    // Given
    setupZoomCalculatorObjects(objects, center, expected_particle);

    // When
    zoom_calculator.zoomIn(objects);

    // Then
    const Vector expected_displacement_from_center = {20, 40};
    const Vector expected_position = expected_displacement_from_center + center;

    ASSERT_EQ(expected_position, objects.dot_data.dots[0].getDisplayPosition());
}

TEST_F(ZoomCalculatorFixture, zoom_out_makes_dots_display_closer_to_center)
{
    // Given
    setupZoomCalculatorObjects(objects, center, expected_particle);

    // When
    zoom_calculator.zoomOut(objects);

    // Then
    const Vector expected_displacement_from_center = {5, 10};
    const Vector expected_position = expected_displacement_from_center + center;

    ASSERT_EQ(expected_position, objects.dot_data.dots[0].getDisplayPosition());
}

TEST_F(ZoomCalculatorFixture, zoom_in_makes_rocket_bigger_and_displayed_further_from_center)
{
    // Given
    setupZoomCalculatorObjects(objects, center, expected_particle);

    // When
    zoom_calculator.zoomIn(objects);

    // Then
    const int expected_width = 40;
    const int expected_height = 160;

    const Vector expected_displacement_from_center = {20, 40};
    const Vector expected_display_position = expected_displacement_from_center + center;

    const int actual_width = objects.rocket.getDisplayWidth();
    const int actual_height = objects.rocket.getDisplayHeight();
    const Vector actual_display_position = objects.rocket.getDisplayPosition();

    EXPECT_EQ(expected_width, actual_width);
    EXPECT_EQ(expected_height, actual_height);
    EXPECT_EQ(expected_display_position, actual_display_position);
}

TEST_F(ZoomCalculatorFixture, zoom_out_makes_rocket_smaller_and_closer_to_center)
{
    // Given
    setupZoomCalculatorObjects(objects, center, expected_particle);

    // When
    zoom_calculator.zoomOut(objects);

    // Then
    const int expected_width = 10;
    const int expected_height = 40;

    const Vector expected_displacement_from_center = {5, 10};
    const Vector expected_display_position = expected_displacement_from_center + center;

    const int actual_width = objects.rocket.getDisplayWidth();
    const int actual_height = objects.rocket.getDisplayHeight();
    const Vector actual_display_position = objects.rocket.getDisplayPosition();

    EXPECT_EQ(expected_width, actual_width);
    EXPECT_EQ(expected_height, actual_height);
    ASSERT_EQ(expected_display_position, actual_display_position);
}

TEST_F(ZoomCalculatorFixture, no_zoom_gives_engine_position_no_change)
{
    // Given
    setupZoomCalculatorObjects(objects, center, expected_particle);
    objects.rocket.engines[0].display_line[0] = {110, 110};
    objects.rocket.engines[0].display_line[1] = {120, 110};

    // When
    zoom_calculator.noZoom(objects);

    // Then
    const std::array<Vector, 2> actual_line = objects.rocket.engines[0].display_line;
    const std::array<Vector, 2> expected_line = {Vector{110, 110}, Vector{120, 110}};

    ASSERT_EQ(expected_line, actual_line);
}

TEST_F(ZoomCalculatorFixture, zoom_in_gives_engine_position_further_away)
{
    // Given
    setupZoomCalculatorObjects(objects, center, expected_particle);
    objects.rocket.engines[0].display_line[0] = {110, 110};
    objects.rocket.engines[0].display_line[1] = {120, 110};

    // When
    zoom_calculator.zoomIn(objects);

    // Then
    const std::array<Vector, 2> actual_line = objects.rocket.engines[0].display_line;
    const std::array<Vector, 2> expected_line = {Vector{120, 120}, Vector{140, 120}};

    ASSERT_EQ(expected_line, actual_line);
}

TEST_F(ZoomCalculatorFixture, zoom_out_gives_engine_position_closer)
{
    // Given
    setupZoomCalculatorObjects(objects, center, expected_particle);
    objects.rocket.engines[0].display_line[0] = {110, 110};
    objects.rocket.engines[0].display_line[1] = {120, 110};

    // When
    zoom_calculator.zoomOut(objects);

    // Then
    const std::array<Vector, 2> actual_line = objects.rocket.engines[0].display_line;
    const std::array<Vector, 2> expected_line = {Vector{105, 105}, Vector{110, 105}};

    ASSERT_EQ(expected_line, actual_line);
}
