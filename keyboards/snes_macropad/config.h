// Copyright 2023 John Barbero Unenge (@jbarberu)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP25
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

#define OLED_DISPLAY_128X32
#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN GP14
#define I2C1_SCL_PIN GP15

#ifdef RGB_MATRIX_ENABLE
    #define RGBLED_NUM       1  // Number of LEDs
    #define RGB_MATRIX_LED_COUNT RGBLED_NUM
    #define BACKLIGHT_PWM_DRIVER PWMD4
    #define BACKLIGHT_PWM_CHANNEL RP2040_PWM_CHANNEL_B

    //#define ENABLE_RGB_MATRIX_ALPHAS_MODS
    //#define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
    //#define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
    //#define ENABLE_RGB_MATRIX_BREATHING
    //#define ENABLE_RGB_MATRIX_BAND_SAT
    //#define ENABLE_RGB_MATRIX_BAND_VAL
    //#define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
    //#define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
    //#define ENABLE_RGB_MATRIX_CYCLE_ALL
    //#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
    //#define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
    //#define ENABLE_RGB_MATRIX_RAINDROPS
    //#define ENABLE_RGB_MATRIX_HUE_BREATHING
    //#define ENABLE_RGB_MATRIX_PIXEL_FRACTAL
    //#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
    //#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
    //#define ENABLE_RGB_MATRIX_SOLID_REACTIVE
    //#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
    //#define ENABLE_RGB_MATRIX_SPLASH
    //#define ENABLE_RGB_MATRIX_SOLID_SPLASH
#endif

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
