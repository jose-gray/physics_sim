#ifndef Rocket_H
#define Rocket_H

#include "Engine.h"
#include "RotationalParticle.h"
#include <array>

class Rocket : public RotationalParticle
{
private:
    const float width = 20;
    const float height = 80;
    float display_width = width;
    float display_height = height;

    static const int number_of_vertices = 4;
    std::array<Vector, number_of_vertices> vertices;

    bool is_rocket_frame = false;


public:
    Rocket();

    std::array<Engine, 10> engines;
    bool boost_mode = false;
    bool stabiliserOn = false;
    bool straightnerOn = false;
    bool circularOrbitOn = false;

    float getDisplayWidth() const { return display_width; };
    void setDisplayWidth(const float input_width) { display_width = input_width; };

    float getDisplayHeight() const { return display_height; };
    void setDisplayHeight(const float input_height) { display_height = input_height; };

    float getWidth() const { return width; };
    float getHeight() const { return height; };

    std::array<Vector, number_of_vertices> getVertices() const { return vertices; };
    void setVertices(const std::array<Vector, number_of_vertices> input_vertices) { vertices = input_vertices; };

    bool getIsRocketFrame() const;
    void toggleIsRocketFrame();
};

inline bool operator==(const Rocket &lhs, const Rocket &rhs)
{
    return (RotationalParticle)lhs == (RotationalParticle)rhs &&
           lhs.getDisplayWidth() == rhs.getDisplayWidth() &&
           lhs.getDisplayHeight() == rhs.getDisplayHeight() &&
           lhs.getWidth() == rhs.getWidth() &&
           lhs.getHeight() == rhs.getHeight() &&
           lhs.getVertices() == rhs.getVertices() &&
           lhs.getIsRocketFrame() == rhs.getIsRocketFrame() &&
           lhs.engines == rhs.engines &&
           lhs.boost_mode == rhs.boost_mode &&
           lhs.stabiliserOn == rhs.stabiliserOn;
}

inline bool operator!=(const Rocket &lhs, const Rocket &rhs)
{
    return !(lhs == rhs);
}

inline std::ostream &operator<<(std::ostream &os, const Rocket &rocket)
{
    os << (RotationalParticle)rocket
       << "width: " << rocket.getWidth() << "\n"
       << "height: " << rocket.getHeight() << "\n"
       << "width_disp: " << rocket.getDisplayWidth() << "\n"
       << "height_dips: " << rocket.getDisplayHeight() << "\n"
       << "is_rocket_frame: " << rocket.getIsRocketFrame() << "\n"
       << "engines: ";

    for (Engine engine : rocket.engines)
    {
        os << engine << "\n";
    }

    return os;
}

#endif