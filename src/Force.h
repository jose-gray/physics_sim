#ifndef FORCE_H
#define FORCE_H

#include "vector.h"
#include <iostream>

struct Force
{
    Vector F; //actual force
    Vector b; //application point
};

bool operator==(const Force &lhs, const Force &rhs);

bool operator!=(const Force &lhs, const Force &rhs);

std::ostream &operator<<(std::ostream &os, const Force &force);

#endif
