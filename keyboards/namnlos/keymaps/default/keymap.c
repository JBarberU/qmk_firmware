// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum {
    L_Base,
    L_Lower,
    L_Raise,
};

#define MO_Ra MO(L_Raise)
#define MO_Lo MO(L_Lower)

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
    [L_Base] = LAYOUT(
        KC_NO,  KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                           KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_NO,
        KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                           KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_NO,
        KC_ESC, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                           KC_H,   KC_J,   KC_K,   KC_L,   KC_NO,  KC_NO,
        KC_NO,   KC_Z,   KC_X,  KC_C,   KC_V,   KC_B,                           KC_N,   KC_M,   KC_NO,  KC_NO,  KC_NO,  KC_NO,
        KC_NO,   KC_NO,         MO_Ra,  KC_DEL, KC_BSPC, KC_LSFT,      KC_RSFT, KC_SPC, KC_ENT, MO_Lo,          KC_NO,  KC_NO
    ),
    [L_Raise] = LAYOUT(
        QK_BOOT, KC_NO,  KC_NO,  KC_NO,   KC_NO,  KC_NO,                        KC_A,   KC_B,   KC_C,   KC_D,   KC_E,   KC_F,
        KC_NO,   KC_NO,  KC_NO,  KC_NO,   KC_NO,  KC_NO,                        KC_G,   KC_H,   KC_I,   KC_J,   KC_K,   KC_L,
        KC_NO,   KC_NO,  KC_NO,  KC_NO,   KC_NO,  KC_NO,                        KC_M,   KC_N,   KC_O,   KC_P,   KC_Q,   KC_R,
        KC_NO,   KC_NO,  KC_NO,  KC_NO,   KC_NO,  KC_NO,                        KC_S,   KC_T,   KC_U,   KC_V,   KC_W,   KC_X,
        KC_NO,   KC_NO,          KC_TRNS, KC_NO,  KC_NO,   KC_NO,        KC_0,   KC_1,   KC_2,   KC_3,           KC_Y,   KC_Z
    )
};

const char * get_layer_name_user(uint8_t layer) {
    switch (layer) {
        case L_Base:
            return "Base";
        case L_Lower:
            return "Lower";
        case L_Raise:
            return "Raise";
        default:
            return "Undef";
    }
}
