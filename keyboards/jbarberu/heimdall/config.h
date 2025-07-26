// Copyright 2025 JBarberU (@jbarberu)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Split Comms
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP0
#define SERIAL_USART_RX_PIN GP1

// Flash by double tapping reset
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

// Hand detect
#define MASTER_LEFT
#define SPLIT_HAND_PIN GP10

// Display
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN GP14
#define SPI_MOSI_PIN GP15
#define LCD_DC_PIN GP12
#define LCD_CS_PIN GP16
#define LCD_RST_PIN GP13
#define BACKLIGHT_PWM_DRIVER PWMD2
#define BACKLIGHT_PWM_CHANNEL RP2040_PWM_CHANNEL_B
#define QUANTUM_PAINTER_LVGL_USE_CUSTOM_CONF

// Misc
// Assign MISO to an unused pin, since the default is GP20, which we use
// for column 2.
#define SPI_MISO_PIN GP25
