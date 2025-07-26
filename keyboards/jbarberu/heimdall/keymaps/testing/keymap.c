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
        KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,        KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
        KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,        KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
        KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,        KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
        KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,        KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
        QK_BOOT,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,        KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO
    ),
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        const int row = record->event.key.row;
        const int col = record->event.key.col;
        uprintf("process_record_user -> pressed: r=%d, c=%d, code: %d\n", row, col, keycode);
        if (keycode == QK_BOOT) {
            return true;
        }
    }
    return false;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    const char* const direction = clockwise ? "clockwise" : "counter clockwise";
    uprintf("encoder turned %s\n", direction);
    return false;
}
