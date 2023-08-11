#ifndef ENGINE_H
#define ENGINE_H

#include "../Force.h"
#include "../vector.h"
#include <array>

struct Engine
{
    bool is_on = false;
    Force base_force;

    std::array<Vector, 2> initial_display_line;
    std::array<Vector, 2> display_line;
};

inline bool operator==(const Engine &lhs, const Engine &rhs)
{
    return (lhs.is_on == rhs.is_on &&
            lhs.base_force == rhs.base_force &&
            lhs.display_line == rhs.display_line);
};

inline bool operator!=(const Engine &lhs, const Engine &rhs)
{
    return !(lhs == rhs);
};

inline std::ostream &operator<<(std::ostream &os, const Engine &engine)
{
    os << "on: " << engine.is_on << "\n"
       << "base_force: " << engine.base_force << "\n"
       << "display_line: ";

    for (Vector pos : engine.display_line)
    {
        os << pos << " ";
    };

    return os;
};

#endif
