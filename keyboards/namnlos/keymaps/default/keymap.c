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
#define HR_S LGUI_T(KC_S)
#define HR_D LALT_T(KC_D)
#define HR_F LCTL_T(KC_F)

#define HR_J LCTL_T(KC_J)
#define HR_K LALT_T(KC_K)
#define HR_L LGUI_T(KC_L)

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
        KC_NO,   KC_1,   KC_2,    KC_3,    KC_4,     KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
        KC_TAB,  KC_Q,   KC_W,    KC_E,    KC_R,     KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
        KC_ESC,  KC_A,   HR_S,    HR_D,    HR_F,     KC_G,                         KC_H,    HR_J,    HR_K,    HR_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,   KC_X,    KC_C,    KC_V,     KC_B,                         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_NO,   KC_NO,           MO_Ra,   KC_DEL,   KC_BSPC, KC_LSFT,    KC_RSFT, KC_SPC,  KC_ENT,  MO_Lo,            KC_NO,   KC_NO
    ),
    [L_Raise] = LAYOUT(
        QK_BOOT, KC_NO,  KC_NO,   KC_NO,   KC_NO,    KC_NO,                        KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_NO,
        KC_NO,   KC_NO,  KC_HOME, KC_UP,   KC_END,   KC_PGUP,                      KC_CIRC, KC_AMPR, KC_MINS, KC_EQL,  KC_RBRC, KC_TILD,
        KC_NO,   KC_NO,  KC_LEFT, KC_DOWN, KC_RIGHT, KC_PGDN,                      KC_BSLS, KC_UNDS, KC_LPRN, KC_RPRN, KC_PLUS, KC_GRV,
        KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_NO,    KC_NO,                        KC_ASTR, KC_LBRC, KC_LCBR, KC_RCBR, KC_PIPE, KC_NO,
        KC_NO,   KC_NO,           KC_TRNS, KC_NO,    KC_NO,   KC_NO,        KC_0,  KC_1,    KC_2,    KC_3,             KC_Y,    KC_Z
    ),
    [L_Lower] = LAYOUT(
        KC_NO,   KC_F1,  KC_F2,   KC_F3,   KC_F4,    KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_NO,
        KC_NO,   KC_F11, KC_F12,  KC_F13,  KC_F14,   KC_F15,                       KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_NO,
        KC_NO,   KC_F21, KC_F22,  KC_F23,  KC_F24,   KC_NO,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_NO,    KC_NO,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,   KC_NO,           KC_NO,   KC_NO,    KC_NO,   KC_NO,        KC_NO, KC_NO,   KC_TRNS, KC_NO,            KC_NO,   KC_NO

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
        default:
            return "Undef";
    }
}
