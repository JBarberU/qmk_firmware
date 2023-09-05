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

static void oled_render_layer(void)
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

#if 0
static void test_oled(void)
{
    oled_clear();
    oled_write_P(PSTR("abcdefghijklmnopqrstu"), false);
    oled_write_P(PSTR("abcdefghijklmnopqrstu"), true);
    oled_write_P(PSTR("abcdefghijklmnopqrstu"), false);
    oled_write_P(PSTR("abcdefghijklmnopqrstu"), true);
}
#endif

static void oled_render_keylog(void);

bool oled_task_user(void)
{
    oled_render_layer();
    oled_render_keylog();
    oled_write_ln(PSTR(""), false);
    return false;
}

char     key_name = ' ';
uint16_t last_keycode;
uint8_t  last_row;
uint8_t  last_col;

static const char PROGMEM code_to_name[60] = {' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\', '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

static void set_keylog(uint16_t keycode, keyrecord_t *record) {
    key_name     = ' ';
    last_keycode = keycode;
    if (IS_QK_MOD_TAP(keycode)) {
        if (record->tap.count) {
            keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
        } else {
            keycode = 0xE0 + biton(QK_MOD_TAP_GET_MODS(keycode) & 0xF) + biton(QK_MOD_TAP_GET_MODS(keycode) & 0x10);
        }
    } else if (IS_QK_LAYER_TAP(keycode) && record->tap.count) {
        keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
    } else if (IS_QK_MODS(keycode)) {
        keycode = QK_MODS_GET_BASIC_KEYCODE(keycode);
    } else if (IS_QK_ONE_SHOT_MOD(keycode)) {
        keycode = 0xE0 + biton(QK_ONE_SHOT_MOD_GET_MODS(keycode) & 0xF) + biton(QK_ONE_SHOT_MOD_GET_MODS(keycode) & 0x10);
    }
    if (keycode > ARRAY_SIZE(code_to_name)) {
        return;
    }

    // update keylog
    key_name = pgm_read_byte(&code_to_name[keycode]);
    last_row = record->event.key.row;
    last_col = record->event.key.col;
}

static const char *depad_str(const char *depad_str, char depad_char) {
    while (*depad_str == depad_char)
        ++depad_str;
    return depad_str;
}

static void oled_render_keylog(void) {
    const char *last_row_str = get_u8_str(last_row, ' ');
    oled_write(depad_str(last_row_str, ' '), false);
    oled_write_P(PSTR("x"), false);
    const char *last_col_str = get_u8_str(last_col, ' ');
    oled_write(depad_str(last_col_str, ' '), false);
    oled_write_P(PSTR(", k"), false);
    const char *last_keycode_str = get_u16_str(last_keycode, ' ');
    oled_write(depad_str(last_keycode_str, ' '), false);
    oled_write_P(PSTR(":"), false);
    oled_write_char(key_name, false);
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        set_keylog(keycode, record);
    }
    return process_record_user(keycode, record);
}

void keyboard_post_init_user(void) {
    debug_enable = true;
    debug_matrix = true;
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(HSV_MAGENTA);
    /*rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3);*/
    rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL);
}
