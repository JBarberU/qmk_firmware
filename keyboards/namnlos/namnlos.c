// Copyright 2023 John Barbero Unenge (@jbarberu)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

// oled keylog rendering has been kindly borrowed from crkbd <3

uint8_t  last_row;
uint8_t  last_col;

static void set_keylog(uint16_t keycode, keyrecord_t *record) {
    last_row = record->event.key.row;
    last_col = record->event.key.col;
}

static void oled_render_keylog(void) {
    oled_write_char('0' + last_row, false);
    oled_write("x", false);
    oled_write_char('0' + last_col, false);
}

__attribute__((weak)) const char * get_layer_name_user(uint8_t layer) {
    return get_u8_str(layer, ' ');
}

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;
    }
    else {
        return OLED_ROTATION_270;
    }
    return rotation;
}

__attribute__((weak)) void oled_render_logo_user(void) {
    static const char qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write(qmk_logo, false);
}

static void oled_render_layer(void) {
    oled_write_ln("Layer", false);
    const char* layer_name = get_layer_name_user(get_highest_layer(layer_state));
    if (strlen(layer_name) % 5 == 0) {
        oled_write(layer_name, false);
    }
    else {
        oled_write_ln(layer_name, false);
    }
}

void oled_newlines(int num_lines) {
    for (unsigned int i = 0; i < num_lines; ++i)
    {
        oled_advance_page(true);
    }
}

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }

    if (is_keyboard_master())
    {
        oled_render_keylog();
        oled_newlines(5);
        oled_render_layer();
    }
    else
    {
        oled_render_logo_user();
    }
    return false;
}

static void setupForFlashing(void) {
    oled_clear();
    oled_write("     ", false);
    oled_write("     ", false);
    oled_write("     ", false);
    oled_write("*****", false);
    oled_write("     ", false);
    oled_write("Flash", false);
    oled_write("     ", false);
    oled_write("Mode ", false);
    oled_write("     ", false);
    oled_write("*****", false);
    oled_write("     ", false);
    oled_write("     ", false);
    oled_write("     ", false);
    oled_write("     ", false);
    oled_write("     ", false);
    oled_write("     ", false);

    // Force data to be rendered
    oled_render_dirty(true);

#ifdef RGB_ENABLED
    // Set alternating backlight colors
    const uint8_t max = 20;
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    for (size_t i = 0; i < RGBLED_NUM; ++i) {
        rgb_led_t *led_ = (rgb_led_t *)&led[i];
        switch (i % 2) {
            case 0:
                setrgb(max, 0, max, led_);
                break;
            case 1:
                setrgb(0, max, max, led_);
                break;
        }
    }
    rgblight_set();
#endif
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        set_keylog(keycode, record);
    }
    if (keycode == QK_BOOT) {
        setupForFlashing();
    }
    return process_record_user(keycode, record);
}
