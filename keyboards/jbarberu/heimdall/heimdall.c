// Copyright 2023 John Barbero Unenge (@jbarberu)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#include "display.h"
#include "print.h"

static bool display_enabled;

#if DO_FLASHING_SETUP
static void setupForFlashing(void) {
#ifdef RGB_ENABLED
    print("Started flashing!\n");
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
#endif

static painter_device_t painter;

void keyboard_post_init_kb() {
    debug_enable = true;
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(HSV_MAGENTA);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL);
    backlight_enable();
    
    display_enabled = false;

#ifdef STRONTY_STUFF
    print("Turned backlight on\n");
    if (true || is_keyboard_left()) {
        rgblight_sethsv_noeeprom(HSV_RED);
        display_enabled = display_init_kb();
        if (!display_enabled) {
            rgblight_sethsv_noeeprom(HSV_BLUE);
            print("Failed to initialize display\n");
            // log error
        } else {
            rgblight_sethsv_noeeprom(HSV_GREEN);
            print("Initialized display\n");
        }
    }
#endif

    uprintf("Is master: %s\n", is_keyboard_left() ?
            "yes" : "no");

    const uint16_t SPI_DIVISOR = 32;
    const uint16_t SPI_MODE = 3;
    painter = qp_st7789_make_spi_device(240, 240, 16, 12, 13, SPI_DIVISOR, SPI_MODE);
    qp_set_viewport_offsets(painter, 0, 20);
    qp_init(painter, QP_ROTATION_0);   // Initialise the display
    qp_power(painter, true);
    qp_clear(painter);
    uprintf("Got painter: %d\n", (int)painter);

    keyboard_post_init_user();
}

void housekeeping_task_kb(void) {
    static uint32_t last_draw = 0;
    if (timer_elapsed32(last_draw) > 33) { // Throttle to 30fps
        last_draw = timer_read32();
        uint16_t left = 0;
        uint16_t top = 7;
        uint16_t right = 239;
        uint16_t bottom = 200;
        bool filled = true;
        qp_rect(painter, left, top, right, bottom, HSV_RED, filled);
        
        qp_flush(painter);
        print("Redrawing painter\n");
    }
#ifdef STRONTY_STUFF
    static int counter = 0;
    print("housekeeping_task_kb");
    if (display_enabled) {
        display_housekeeping_task();

        if (counter % 1000 == 0) {
            print("display_enabled -> display_housekeeping_task()\n");
        }
    } else {
        if (counter % 1000 == 0) {
            print("display_disabled !-> display_housekeeping_task()\n");
        }
    }

    counter++;
#endif
}

#ifdef STRONTY_STUFF
bool is_display_enabled(void) {
    return display_enabled;
}
#endif

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        uprintf("Got key event: (%d, %d)\n", record->event.key.row , record->event.key.col);

#ifdef OLED_ENABLED
        set_keylog(keycode, record);
#endif
    }

#if DO_FLASHING_SETUP
    if (keycode == QK_BOOT) {
        setupForFlashing();
    }
#endif

    return false; //process_record_user(keycode, record);
}
