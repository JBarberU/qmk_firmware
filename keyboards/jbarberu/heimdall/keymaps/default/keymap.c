// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum {
    L_Base,
    L_Lower,
    L_Raise,
    L_Gaming
};

#define MO_Ra LT(L_Raise, KC_BSPC)
#define MO_Lo LT(L_Lower, KC_SPC)
#define HR_S LGUI_T(KC_S)
#define HR_D LALT_T(KC_D)
#define HR_F LCTL_T(KC_F)

#define HR_J LCTL_T(KC_J)
#define HR_K LALT_T(KC_K)
#define HR_L LGUI_T(KC_L)

#define JB_CLW LCTL(KC_COMM)

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
        KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,     KC_T,
        KC_ESC,  KC_A,    HR_S,    HR_D,    HR_F,     KC_G,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,     KC_B,
        KC_NO,   KC_NO,            KC_NO,   KC_DEL,   MO_Ra, KC_LSFT
    ),
    [L_Raise] = LAYOUT(
        QK_BOOT, KC_NO,   KC_NO,   KC_NO,   JB_CLW,   KC_NO,
        KC_NO,   KC_HOME, KC_PGUP, KC_PGDN, KC_END,   KC_EXLM,
        KC_NO,   KC_LEFT, KC_UP,   KC_DOWN, KC_RIGHT, KC_DLR,
        KC_NO,   KC_NO,   KC_NO,   KC_PERC, KC_HASH,  KC_AT,
        KC_NO,   KC_NO,            KC_NO,   KC_TRNS,  KC_TRNS, KC_TRNS
    ),
    [L_Lower] = LAYOUT(
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,
        KC_NO,   KC_1,    KC_2,    KC_3,    KC_4,     KC_5,
        KC_NO,   KC_6,    KC_7,    KC_8,    KC_9,     KC_0,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,
        KC_NO,   KC_NO,            KC_NO,   KC_TRNS,  KC_TRNS, KC_TRNS
    ),
    [L_Gaming] = LAYOUT(
        KC_NO,   KC_1,   KC_2,    KC_3,    KC_4,     KC_5,
        KC_TAB,  KC_NO,  KC_NO,   KC_COMM, KC_D,     KC_NO,
        KC_ESC,  KC_NO,  KC_A,    KC_SCLN, KC_H,     KC_NO,
        KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_I,     KC_V,
        KC_NO,   KC_NO,           KC_NO,   KC_NO,    KC_NO,   KC_NO
    )
    /* Blank layer
    [<< layer name >>] = LAYOUT(
        KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_NO,    KC_NO,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_NO,    KC_NO,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_NO,    KC_NO,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_NO,    KC_NO,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,           KC_NO,   KC_NO,    KC_NO,   KC_NO,        KC_NO, KC_NO,   KC_NO,   KC_NO,            KC_NO,   KC_NO
    )
    */
};

const char * get_layer_name_user(uint8_t layer) {
    switch (layer) {
        case L_Base:
            return "Base";
        case L_Lower:
            return "Lower";
        case L_Raise:
            return "Raise";
        case L_Gaming:
            return "Gamin";
        default:
            return "Undef";
    }
}
