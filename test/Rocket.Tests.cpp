#include "../src/objects/rocket.h"

#include <gtest/gtest.h>

class VerticesParameterizedTestFixture : public ::testing::TestWithParam<int>
{
protected:
    Rocket rocket;
};

TEST(rocket, vertices_can_be_set)
{
    // given
    Rocket rocket;

    const Vector a_vertex = {1, 2};

    const std::array<Vector, 4> vertices = {a_vertex, a_vertex, a_vertex, a_vertex};

    // when
    rocket.setVertices(vertices);

    // then
    const std::array<Vector, 4> actual_vertices = rocket.getVertices();

    ASSERT_EQ(vertices, actual_vertices);
}

TEST(rocket, rocket_frame_default_false)
{
    // given
    Rocket rocket;

    // when
    const bool actual_is_rocket_frame = rocket.getIsRocketFrame();

    // then
    ASSERT_FALSE(actual_is_rocket_frame);
}

TEST(rocket, rocket_frame_can_be_set_true)
{
    // given
    Rocket rocket;

    // when
    rocket.toggleIsRocketFrame();

    // then
    const bool actual_is_rocket_frame = rocket.getIsRocketFrame();

    ASSERT_TRUE(actual_is_rocket_frame);
}

