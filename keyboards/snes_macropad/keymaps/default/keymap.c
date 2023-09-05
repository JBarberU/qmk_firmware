// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum Layer
{
    L_Default = 0,
    L_Lower,
    L_Raise,
    L_Adjust
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * Macropad Button Order
     * ┌───┬───┬───┬───┐
     * │ 7 │ 8 │ 9 │ - │
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ + │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ 0 │
     * └───┴───┴───┴───┘
     *
     * SNES Button Order
     * ┌────────┬────────┬────────┬────────┐
     * │   LT   │   RT   │ START  │ SELECT │
     * ├────────┼────────┼────────┼────────┤
     * │   UP   │  DOWN  │  LEFT  │ RIGHT  │
     * ├────────┼────────┼────────┼────────┤
     * │   A    │   B    │   X    │   Y    │
     * └────────┴────────┴────────┴────────┘
     *
     */
    [L_Default] = LAYOUT(
          /*LT(1, KC_1), LT(2, KC_P2), LT(3, KC_P3), KC_NO*/
          KC_7,       KC_8,        KC_9,        KC_MINS
        , KC_4,       KC_5,        LT(1, KC_6), KC_EQL
        , KC_1,       KC_2,        KC_3,        KC_0

        , KC_A,    KC_B,    KC_C,    KC_D
        , KC_E,    LT(1, KC_F),    KC_G,    KC_H
        , KC_I,    KC_J,    KC_K,    KC_L
    ),
    [L_Lower] = LAYOUT(
          KC_NO,   KC_NO,   KC_NO,   KC_NO
        , KC_NO,   QK_RBT,  KC_TRNS, QK_BOOT
        , KC_NO,   KC_NO,   KC_NO,   KC_NO

        , KC_A,    KC_B,    KC_C,    KC_D
        , QK_BOOT,    KC_TRNS,    KC_G,    KC_H
        , KC_I,    KC_J,    KC_K,    KC_L
    ),
    [L_Raise] = LAYOUT(
          KC_NO,   KC_NO,   KC_NO,   KC_NO
        , KC_NO,   RGB_M_B, KC_NO,   KC_NO
        , RGB_TOG, KC_TRNS, RGB_M_P, KC_NO

        , KC_A,    KC_B,    KC_C,    KC_D
        , KC_E,    KC_F,    KC_G,    KC_H
        , KC_I,    KC_J,    KC_K,    KC_L
    ),
    [L_Adjust] = LAYOUT(
          KC_NO,   KC_P8,   KC_NO,   KC_NO
        , KC_NO,   RGB_HUD, KC_NO,   KC_NO
        , RGB_HUI, KC_NO,   KC_TRNS, KC_NO

        , KC_A,    KC_B,    KC_C,    KC_D
        , KC_E,    KC_F,    KC_G,    KC_H
        , KC_I,    KC_J,    KC_K,    KC_L
    )
};

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return rotation;
}

void print_layer(void)
{
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case L_Default:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case L_Lower:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case L_Raise:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case L_Adjust:
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
    debug_enable = true;
    debug_matrix = true;
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(HSV_MAGENTA);
    /*rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3);*/
    rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL);
}
