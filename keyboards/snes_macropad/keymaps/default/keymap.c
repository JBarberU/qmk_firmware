// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │ 7 │ 8 │ 9 │ / │
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ * │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ - │
     * ├───┼───┼───┼───┤
     * │ 0 │ . │Ent│ + │
     * └───┴───┴───┴───┘
     */
    [0] = LAYOUT_ortho_4x4(
        KC_P7,   KC_P8,   KC_P9,   KC_PSLS,
        KC_P4,   QK_BOOT,   KC_P6,   KC_PAST,
        KC_P1,   KC_P2,   KC_P3,   KC_PMNS
    )
};

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return rotation;
}

void print_layer(void)
{
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case 1:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case 2:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case 3:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
            break;
    }
}

void test_oled(void)
{
    oled_clear();
    oled_write_P(PSTR("abcdefghijklmnopqrstu"), false);
    oled_write_P(PSTR("abcdefghijklmnopqrstu"), true);
    oled_write_P(PSTR("abcdefghijklmnopqrstu"), false);
    oled_write_P(PSTR("abcdefghijklmnopqrstu"), true);
}

bool oled_task_user(void)
{
    static bool needs_update = true;
    if (needs_update)
    {
        print_layer();
        needs_update = false;
    }
    return false;
}
