#ifndef Vector_H
#define Vector_H

#include <iostream>
#include <math.h>
#include <optional>

#ifndef PI
#define PI 3.14159265358979323846f // Required as PI is not always defined in math.h
#endif

class Vector
{
public:
    Vector(float x, float y) : x(x), y(y){};
    Vector(int x, int y) : x(float(x)), y(float(y)){};
    Vector() : x(0), y(0){};
    Vector(const std::initializer_list<float> &list) : x(list.begin()[0]), y(list.begin()[1]){};

    float getx() const { return x; };
    void setx(const float x_input) { x = x_input; };
    void setx(const int x_input) { x = x_input; };

    float gety() const { return y; };
    void sety(const float y_input) { y = y_input; };
    void sety(const int y_input) { y = y_input; };

    float getMagnitude() const;

    std::optional<Vector> getDirectionVector() const;

    void rotateVector(float cos_angle, float sin_angle);
    void rotateVector(float angle);

    void operator+=(const Vector &rhs)
    {
        x += rhs.x;
        y += rhs.y;
    };

    Vector operator+(const Vector &rhs) const
    {
        return Vector(x + rhs.x, y + rhs.y);
    };

    Vector operator-(const Vector &rhs) const
    {
        return Vector(x - rhs.x, y - rhs.y);
    };

    void operator=(const Vector &rhs)
    {
        x = rhs.x;
        y = rhs.y;
    };

    void operator=(const std::initializer_list<float> &rhs)
    {
        x = rhs.begin()[0];
        y = rhs.begin()[1];
    };

    Vector operator*(const float &rhs) const
    {
        return Vector(x * rhs, y * rhs);
    };

    Vector operator/(const float &rhs) const
    {
        return Vector(x / rhs, y / rhs);
    };

    float operator[](const int index) const
    {
        if (index == 0)
        {
            return x;
        }
        return y;
    }

private:
    float x;
    float y;
};

bool operator==(const Vector &lhs, const Vector &rhs);

inline Vector operator*(const float &lhs, const Vector &rhs)
{
    return Vector(lhs * rhs.getx(), lhs * rhs.gety());
};

inline float dotProduct(const Vector vector_1, const Vector vector_2)
{
    return vector_1[0] * vector_2[0] + vector_1[1] * vector_2[1];
};

inline float crossProduct(const Vector vector_1, const Vector vector_2)
{
    return vector_1[0] * vector_2[1] - vector_1[1] * vector_2[0];
};

inline float calculateAngle(const Vector vector)
{
    float angle;

    if (vector[0] > 0 && vector[1] > 0)
    {
        angle = atan(vector[1] / vector[0]);
    }
    else if (vector[0] < 0 && vector[1] > 0)
    {
        angle = atan(vector[1] / vector[0]);
        angle += PI;
    }
    else if (vector[0] < 0 && vector[1] < 0)
    {
        angle = atan(vector[1] / vector[0]);
        angle += PI;
    }
    else if (vector[0] > 0 && vector[1] < 0)
    {
        angle = atan(vector[1] / vector[0]);
        angle += 2 * PI;
    }
    else if (vector[1] == 0)
    {
        if (vector[0] < 0)
        {
            angle = PI;
        }
        else
        {
            angle = 0;
        }
    }
    else if (vector[0] == 0)
    {
        if (vector[1] > 0)
        {
            angle = PI / 2;
        }
        else
        {
            angle = 3 * PI / 2;
        }
    }

    return angle;
};

std::ostream &operator<<(std::ostream &os, const Vector &vector);

#endif
