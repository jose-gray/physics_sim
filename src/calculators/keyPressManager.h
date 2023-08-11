#ifndef keyPressManager_H
#define keyPressManager_H

#include "../Vector.h"
#include "raylib.h"
#include <array>

struct KeyPressFlags
{
    bool switch_frame = false;
    bool engine_on = false;
    bool engine_boost = false;
    Vector engine_direction = {0, 0};
    bool return_to_home = false;
    bool reset_dots = false;
    bool zoom_in = false;
    bool zoom_out = false;
    std::array<bool, 10> number_pad_engine = {false, false, false, false, false, false, false, false, false, false};
    bool circular_orbit_toggle = false;
};

class KeyPressManager
{
public:
    void updateKeyPressFlags(KeyPressFlags &key_press_flags);

private:
};

#endif
