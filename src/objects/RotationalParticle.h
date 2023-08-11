#ifndef ROTATIONALPARTICLE_H
#define ROTATIONALPARTICLE_H

#include "../Vector.h"
#include "LinearParticle.h"

class RotationalParticle : public LinearParticle
{
private:
    Vector com = {0, 0};
    float angle = 0;
    float velocity_angular = 0;
    float acceleration_angular = 0;
    float I = 10000;

public:
    void setCom(const Vector input_com) { com = input_com; };
    Vector getCom() const { return com; };

    void setAngle(const float input_angle) { angle = input_angle; };
    float getAngle() const { return angle; };

    void setVelocity_Angular(const float input_velocity_angular) { velocity_angular = input_velocity_angular; };
    float getVelocity_Angular() const { return velocity_angular; };

    void setAcceleration_Angular(const float input_acceleration_angular) { acceleration_angular = input_acceleration_angular; };
    float getAcceleration_Angular() const { return acceleration_angular; };

    void setI(const float input_I) { I = input_I; };
    float getI() const { return I; };

    Vector getDirectionVector() const;
};

inline bool operator==(const RotationalParticle &lhs, const RotationalParticle &rhs)
{
    return (LinearParticle)lhs == (LinearParticle)rhs &&
           lhs.getCom() == rhs.getCom() &&
           lhs.getAngle() == rhs.getAngle() &&
           lhs.getVelocity_Angular() == rhs.getVelocity_Angular() &&
           lhs.getAcceleration_Angular() == rhs.getAcceleration_Angular() &&
           lhs.getI() == rhs.getI();
}

inline bool operator!=(const RotationalParticle &lhs, const RotationalParticle &rhs)
{
    return !(lhs == rhs);
}

inline std::ostream &operator<<(std::ostream &os, const RotationalParticle &particle)
{
    os << (LinearParticle)particle
       << "com: " << particle.getCom() << "\n"
       << "angle: " << particle.getAngle() << "\n"
       << "angle_v: " << particle.getVelocity_Angular() << "\n"
       << "angle_a: " << particle.getAcceleration_Angular() << "\n"
       << "I: " << particle.getI() << "\n";

    return os;
}

#endif