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
        KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_P5,   KC_NO,   KC_NO,
        LT(1, KC_1),   LT(2, KC_P2),   LT(3, KC_P3),   KC_NO
    ),
    [1] = LAYOUT_ortho_4x4(
        KC_NO,   KC_NO,     KC_NO,   KC_NO,
        KC_NO,   QK_BOOT,   KC_NO,   KC_NO,
        KC_TRNS,   QK_RBT,   KC_BSPC,   KC_NO
    ),
    [2] = LAYOUT_ortho_4x4(
        KC_NO,   KC_NO,     KC_NO,   KC_NO,
        KC_NO,   RGB_M_B,     KC_NO,   KC_NO,
        RGB_TOG,   KC_TRNS,   RGB_M_P,   KC_NO
    ),
    [3] = LAYOUT_ortho_4x4(
        KC_NO,   KC_P8,     KC_NO,   KC_NO,
        KC_NO,   RGB_HUD,   KC_NO,   KC_NO,
        RGB_HUI,   KC_NO,   KC_TRNS,   KC_NO
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
    print_layer();
    return false;
}

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(HSV_MAGENTA);
    /*rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3);*/
    rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL);
}
