#include "Force.h"

bool operator==(const Force &lhs, const Force &rhs)
{
    return (lhs.F == rhs.F && lhs.b == rhs.b);
};

bool operator!=(const Force &lhs, const Force &rhs)
{
    return !(lhs == rhs);
};

std::ostream &operator<<(std::ostream &os, const Force &force)
{
    os << "F: " << force.F << " "
       << " b: " << force.b << " ";

    return os;
};
