#include "Vector.h"

float Vector::getMagnitude() const
{
    return sqrt(x * x + y * y);
}

std::optional<Vector> Vector::getDirectionVector() const
{
    const float magnitude = getMagnitude();
    if (magnitude != 0)
    {
        return Vector(x / magnitude, y / magnitude);
    }

    return {};
}

void Vector::rotateVector(float cos_angle, float sin_angle)
{
    const float x_original = x;
    const float y_original = y;

    x = x_original * cos_angle - y_original * sin_angle;
    y = x_original * sin_angle + y_original * cos_angle;
}

void Vector::rotateVector(const float angle)
{
    const float x_original = x;
    const float y_original = y;

    const float cos_angle = cos(angle);
    const float sin_angle = sin(angle);

    x = x_original * cos_angle - y_original * sin_angle;
    y = x_original * sin_angle + y_original * cos_angle;
}

bool operator==(const Vector &lhs, const Vector &rhs)
{
    bool result = false;

    const bool are_equal = lhs.getx() == rhs.getx() && lhs.gety() == rhs.gety();

    float mean_magnitude = lhs.getMagnitude() / 2 + rhs.getMagnitude() / 2;

    const float x_dif = abs(lhs.getx() - rhs.getx());
    const float thousandth_of_x = mean_magnitude / 1000;
    const bool x_is_near = x_dif <= thousandth_of_x;

    const float y_dif = abs(lhs.gety() - rhs.gety());
    const float thousandth_of_y = mean_magnitude / 1000;
    const bool y_is_near = y_dif <= thousandth_of_y;

    bool is_near = x_is_near && y_is_near;

    if (are_equal || is_near)
    {
        result = true;
    }

    return result;
}

std::ostream &operator<<(std::ostream &os, const Vector &Vector)
{
    os << "(" << Vector.getx() << ", " << Vector.gety() << ")";
    return os;
}
