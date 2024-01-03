// Copyright 2023 John Barbero Unenge (@jbarberu)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN GP14
#define I2C1_SCL_PIN GP15

#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_RX_PIN GP11
#define SERIAL_USART_TX_PIN GP12

// Prototype has:
// - LH -> GND
// - RH -> +3V3
#define MASTER_LEFT
#define SPLIT_HAND_PIN GP23
#define SPLIT_HAND_PIN_LOW_IS_LEFT

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
