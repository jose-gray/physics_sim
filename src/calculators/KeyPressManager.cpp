#include "keyPressManager.h"

void KeyPressManager::updateKeyPressFlags(KeyPressFlags &key_press_flags)
{
    key_press_flags.switch_frame = IsKeyPressed(KEY_BACKSPACE);

    key_press_flags.return_to_home = IsKeyPressed(KEY_ENTER);

    key_press_flags.reset_dots = IsKeyPressed(KEY_ENTER);

    key_press_flags.zoom_in = IsKeyPressed(KEY_KP_ADD);

    key_press_flags.zoom_out = IsKeyPressed(KEY_KP_SUBTRACT);

    key_press_flags.engine_boost = IsKeyDown(KEY_SPACE);

    key_press_flags.number_pad_engine[0] = IsKeyDown(KEY_KP_0);
    key_press_flags.number_pad_engine[1] = IsKeyDown(KEY_KP_1);
    key_press_flags.number_pad_engine[2] = IsKeyDown(KEY_KP_2);
    key_press_flags.number_pad_engine[3] = IsKeyDown(KEY_KP_3);
    key_press_flags.number_pad_engine[4] = IsKeyDown(KEY_KP_4);
    key_press_flags.number_pad_engine[5] = IsKeyDown(KEY_KP_5);
    key_press_flags.number_pad_engine[6] = IsKeyDown(KEY_KP_6);
    key_press_flags.number_pad_engine[7] = IsKeyDown(KEY_KP_7);
    key_press_flags.number_pad_engine[8] = IsKeyDown(KEY_KP_8);
    key_press_flags.number_pad_engine[9] = IsKeyDown(KEY_KP_9);

    key_press_flags.circular_orbit_toggle = IsKeyPressed(KEY_KP_DECIMAL);
}
