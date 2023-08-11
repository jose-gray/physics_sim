#include "../src/vector.h"

#include <gtest/gtest.h>

TEST(vector, booleanOperator_equalVectors_returnsTrue)
{
    // given
    Vector vector_1 = {1, 2};
    Vector vector_2 = {1, 2};

    // then
    ASSERT_EQ(vector_1, vector_2);
}

TEST(vector, booleanOperator_differentXValue_returnsFalse)
{
    // given
    Vector vector_1 = {1, 2};
    Vector vector_2 = {2, 2};

    bool boolean_result = vector_1 == vector_2;

    // then
    ASSERT_FALSE(boolean_result);
}

TEST(vector, booleanOperator_differentYValue_returnsFalse)
{
    // given
    Vector vector_1 = {1, 2};
    Vector vector_2 = {1, 3};

    bool boolean_result = vector_1 == vector_2;

    // then
    ASSERT_FALSE(boolean_result);
}

TEST(vector, booleanOperator_VectorsWithLessThanThousanthDifferenceX_returnsTrue)
{
    // given
    const float vector_one_x_position = 1;

    const float one_thousanth_x_difference = 0.001;
    const float slightly_less_than_one_thousanth_x_difference = 0.001 - 0.0001;

    const float vector_2_x_position = vector_one_x_position + slightly_less_than_one_thousanth_x_difference;

    Vector vector_1 = {vector_one_x_position, 0};
    Vector vector_2 = {vector_2_x_position, 0};

    // then
    ASSERT_EQ(vector_1, vector_2);
}

TEST(vector, booleanOperator_VectorsWithLessThanThousanthDifferenceY_returnsTrue)
{
    // given
    const float vector_one_y_position = 1;

    const float one_thousanth_y_difference = 0.001;
    const float slightly_less_than_one_thousanth_y_difference = 0.001 - 0.0001;

    const float vector_2_y_position = vector_one_y_position + slightly_less_than_one_thousanth_y_difference;

    Vector vector_1 = {0, vector_one_y_position};
    Vector vector_2 = {0, vector_2_y_position};

    // then
    ASSERT_EQ(vector_1, vector_2);
}

TEST(vector, booleanOperator_TwoZeroVectors_returnsTrue)
{
    // given
    Vector vector_1 = {0, 0};
    Vector vector_2 = {0, 0};

    // then
    ASSERT_EQ(vector_1, vector_2);
}

TEST(vector, equals_vector)
{
    // given
    Vector vector_1 = {1, 2};
    Vector vector_2 = {5, 6};

    // when
    vector_1 = vector_2;

    // then
    ASSERT_EQ(vector_1, vector_2);
}

TEST(vector, equals_braces)
{
    // given
    Vector vector_1 = {1, 2};

    // when

    // then
    Vector expected_vector = {1, 2};
    ASSERT_EQ(expected_vector, vector_1);
}

TEST(vector, equals_braces_after_initliasation)
{
    // given
    Vector vector_1;

    // when
    vector_1 = {1, 2};

    // then
    Vector expected_vector = {1, 2};
    ASSERT_EQ(expected_vector, vector_1);
}

TEST(vector, addition)
{
    // given
    Vector vector_1 = {1, 2};
    Vector vector_2 = {2, 4};

    // when
    Vector vector_sum = vector_1 + vector_2;

    // then
    Vector expected_vector_sum(3, 6);

    ASSERT_EQ(expected_vector_sum, vector_sum);
}

TEST(vector, subtraction)
{
    // given
    Vector vector_1 = {1, 2};
    Vector vector_2 = {2, 4};

    // when
    Vector vector_sub = vector_1 - vector_2;

    // then
    Vector expected_vector_sub(-1, -2);

    ASSERT_EQ(expected_vector_sub, vector_sub);
}

TEST(vector, plus_equals)
{
    // given
    Vector vector_1 = {1, 2};
    Vector vector_2 = {5, 6};

    // when
    vector_1 += vector_2;

    // then
    Vector expected_vector_1 = {6, 8};
    ASSERT_EQ(expected_vector_1, vector_1);
}

TEST(vector, multiply_by_scalar)
{
    // given
    Vector vector_1 = {1, 2};

    // when
    Vector vector_2 = vector_1 * 3;
    Vector Vector_3 = 3 * vector_1;

    // then
    Vector expected_vector = {3, 6};
    ASSERT_EQ(expected_vector, vector_2);
    ASSERT_EQ(expected_vector, Vector_3);
}

TEST(vector, divide_by_scalar)
{
    // given
    Vector vector_1 = {6, -3};

    // when
    Vector vector_2 = vector_1 / 3;

    // then
    Vector expected_vector = {2, -1};
    ASSERT_EQ(expected_vector, vector_2);
}

TEST(vector, square_brackets)
{
    // given
    Vector vector_1 = {6, -3};

    // when
    const float x = vector_1[0];
    const float y = vector_1[1];

    // then
    const float expected_x = 6;
    const float expected_y = -3;
    ASSERT_EQ(expected_x, x);
    ASSERT_EQ(expected_y, y);
}

TEST(vector, magnitude)
{
    // given
    Vector vector_1 = {3, 4};

    // when
    float actual_magnitude = vector_1.getMagnitude();

    // then
    float expected_magnitude = 5;
    ASSERT_EQ(expected_magnitude, actual_magnitude);
}

TEST(vector, direction_vector)
{
    // given
    Vector vector_1 = {3, 4};

    // when
    Vector actual_direction_vector = *vector_1.getDirectionVector();

    // then
    Vector expected_direction_vector = {0.6, 0.8};
    ASSERT_EQ(expected_direction_vector, actual_direction_vector);
}

TEST(vector, direction_vector_of_zero_vector)
{
    // given
    Vector vector_1 = {0, 0};

    // when
    auto actual_direction_vector = vector_1.getDirectionVector();

    // then
    ASSERT_FALSE(actual_direction_vector);
}

TEST(vector, rotate_no_rotation)
{
    // given
    Vector vector_1 = {1, 2};

    const float cos_angle = cos(0);
    const float sin_angle = sin(0);

    // when
    vector_1.rotateVector(cos_angle, sin_angle);

    // then
    Vector expected_rotated_vector = {1, 2};

    ASSERT_EQ(expected_rotated_vector, vector_1);
}

TEST(vector, rotate_90_degrees)
{
    // given
    Vector vector_1 = {1, 2};

    const float cos_angle = cos(PI / 2);
    const float sin_angle = sin(PI / 2);

    // when
    vector_1.rotateVector(cos_angle, sin_angle);

    // then
    Vector expected_rotated_vector = {-2, 1};

    ASSERT_EQ(expected_rotated_vector, vector_1);
}

TEST(vector, rotate_180_degrees)
{
    // given
    Vector vector_1 = {1, 2};

    const float cos_angle = cos(PI);
    const float sin_angle = sin(PI);

    // when
    vector_1.rotateVector(cos_angle, sin_angle);

    // then
    Vector expected_rotated_vector = {-1, -2};

    ASSERT_EQ(expected_rotated_vector, vector_1);
}

TEST(vector, rotate_270_degrees)
{
    // given
    Vector vector_1 = {1, 2};

    const float cos_angle = cos(3 * PI / 2);
    const float sin_angle = sin(3 * PI / 2);

    // when
    vector_1.rotateVector(cos_angle, sin_angle);

    // then
    Vector expected_rotated_vector = {2, -1};

    ASSERT_EQ(expected_rotated_vector, vector_1);
}

TEST(vector, rotate_90_degrees_with_angle)
{
    // given
    Vector vector_1 = {1, 2};

    const float angle = PI / 2;

    // when
    vector_1.rotateVector(angle);

    // then
    Vector expected_rotated_vector = {-2, 1};

    ASSERT_EQ(expected_rotated_vector, vector_1);
}

TEST(vector, print)
{
    // Given
    Vector vector_1(1, 2);
    std::string expectedStreamString = "(1, 2)";

    // When
    std::stringstream actualStream;
    actualStream << vector_1;

    // Then
    ASSERT_EQ(expectedStreamString, actualStream.str());
}

TEST(vector, dot_product)
{
    // Given
    Vector vector_1(1, 2);
    Vector vector_2(3, -1);

    // When
    const float actual_dot_product = dotProduct(vector_1, vector_2);

    // Then
    const float expected_dot_product = 1;

    ASSERT_EQ(expected_dot_product, actual_dot_product);
}

TEST(vector, cross_product)
{
    // Given
    Vector vector_1(1, 2);
    Vector vector_2(3, -1);

    // When
    const float actual_cross_product = crossProduct(vector_1, vector_2);

    // Then
    const float expected_cross_product = -7;

    ASSERT_EQ(expected_cross_product, actual_cross_product);
}

TEST(vector, angle_0)
{
    // Given
    Vector vector(1, 0);

    // When
    const float actual_angle = calculateAngle(vector);

    // Then
    const float expected_angle = 0;

    ASSERT_EQ(expected_angle, actual_angle);
}

TEST(vector, angle_45)
{
    // Given
    Vector vector(1, 1);

    // When
    const float actual_angle = calculateAngle(vector);

    // Then
    const float expected_angle = PI / 4;

    ASSERT_EQ(expected_angle, actual_angle);
}

TEST(vector, angle_90)
{
    // Given
    Vector vector(0, 1);

    // When
    const float actual_angle = calculateAngle(vector);

    // Then
    const float expected_angle = PI / 2;

    ASSERT_EQ(expected_angle, actual_angle);
}

TEST(vector, angle_135)
{
    // Given
    Vector vector(-1, 1);

    // When
    const float actual_angle = calculateAngle(vector);

    // Then
    const float expected_angle = 3 * PI / 4;

    ASSERT_EQ(expected_angle, actual_angle);
}

TEST(vector, angle_180)
{
    // Given
    Vector vector(-1, 0);

    // When
    const float actual_angle = calculateAngle(vector);

    // Then
    const float expected_angle = PI;

    ASSERT_EQ(expected_angle, actual_angle);
}

TEST(vector, angle_225)
{
    // Given
    Vector vector(-1, -1);

    // When
    const float actual_angle = calculateAngle(vector);

    // Then
    const float expected_angle = 5 * PI / 4;

    ASSERT_EQ(expected_angle, actual_angle);
}

TEST(vector, angle_270)
{
    // Given
    Vector vector(0, -1);

    // When
    const float actual_angle = calculateAngle(vector);

    // Then
    const float expected_angle = 3 * PI / 2;

    ASSERT_EQ(expected_angle, actual_angle);
}

TEST(vector, angle_315)
{
    // Given
    Vector vector(1, -1);

    // When
    const float actual_angle = calculateAngle(vector);

    // Then
    const float expected_angle = 7 * PI / 4;

    ASSERT_EQ(expected_angle, actual_angle);
}

TEST(vector, angle_zero_vector)
{
    // Given
    Vector vector(0, 0);

    // When
    const float actual_angle = calculateAngle(vector);

    // Then
    const float expected_angle = 0;

    ASSERT_EQ(expected_angle, actual_angle);
}
