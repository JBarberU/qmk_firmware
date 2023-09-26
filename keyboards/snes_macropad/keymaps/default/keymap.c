// vim: shiftwidth=2
// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum Layer
{
  L_Numpad = 0,
  L_Symbols,
  L_EasyEDA,
  L_RGB,
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
  [L_Numpad] = LAYOUT(
      KC_P7,   KC_P8,   KC_P9,   TO(L_EasyEDA)
    , KC_P4,   KC_P5,   KC_P6,   LT(L_Symbols, KC_PCMM)
    , KC_P1,   KC_P2,   KC_P3,   KC_P0

    , KC_A,    KC_S,    KC_ENT,  KC_BSPC
    , KC_UP,   KC_DOWN, KC_LEFT, KC_RIGHT
    , KC_X,    KC_Z,    LSFT(KC_F1),KC_TAB
  ),
  [L_EasyEDA] = LAYOUT(
      KC_COMM, KC_DOT,  KC_K,   TO(L_RGB)
    , KC_LSFT, KC_M,    KC_N,    TO(L_Numpad)
    , KC_LCTL, KC_SPC,  KC_DEL,  KC_BSPC

    , KC_A,    KC_B,    KC_C,    KC_D
    , QK_BOOT,    KC_TRNS,    KC_G,    KC_H
    , KC_I,    KC_J,    KC_K,    KC_L
  ),
  [L_RGB] = LAYOUT(
      RGB_M_P,  RGB_M_B, RGB_TOG, TO(L_Adjust)
    , RGB_MOD,  RGB_HUI, RGB_VAI, TO(L_Numpad)
    , RGB_RMOD, RGB_HUD, RGB_VAD, KC_NO

    , KC_A,    KC_B,    KC_C,    KC_D
    , KC_E,    KC_F,    KC_G,    KC_H
    , KC_I,    KC_J,    KC_K,    KC_L
  ),
  [L_Adjust] = LAYOUT(
      KC_NO,   KC_P8,   KC_NO,   KC_NO
    , KC_NO,   RGB_HUD, KC_NO,   TO(L_Numpad)
    , RGB_HUI, KC_NO,   KC_TRNS, KC_NO

    , KC_A,    KC_B,    KC_C,    KC_D
    , KC_E,    KC_F,    KC_G,    KC_H
    , KC_I,    KC_J,    KC_K,    KC_L
  ),
  [L_Symbols] = LAYOUT(
      KC_PPLS, KC_PMNS, KC_PEQL, KC_NO
    , KC_PAST, KC_PSLS, KC_ENT,  KC_TRNS
    , KC_NUM,  KC_NO,   KC_NO,   QK_BOOT

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

  switch (get_highest_layer(layer_state))
  {
    case L_Numpad:
      oled_write_ln_P(PSTR("Numpad"), false);
      break;
    case L_EasyEDA:
      oled_write_ln_P(PSTR("EasyEDA"), false);
      break;
    case L_RGB:
      oled_write_ln_P(PSTR("RGB Controls"), false);
      break;
    case L_Adjust:
      oled_write_ln_P(PSTR("Adjust"), false);
      break;
    case L_Symbols:
      oled_write_ln_P(PSTR("Symbols"), false);
      break;
    default:
      oled_write_ln_P(PSTR("Undef"), false);
      break;
  }
}

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

static void setupForFlashing(void)
{
  oled_clear();
  oled_write("                     ", false);
  oled_write("  In flash mode...   ", false);
  oled_write("                     ", false);
  oled_write("                     ", false);

  // QMK is clever about only rendering a certain number of chunks per frame,
  // but since the device will go into flash mode right after this call,
  // we want to override this behavior and force all the chunks to be sent to
  // the display immediately.
  const size_t numIterations = OLED_DISPLAY_WIDTH * OLED_DISPLAY_HEIGHT / OLED_UPDATE_PROCESS_LIMIT;
  for (size_t num = 0; num < numIterations; ++num)
    oled_render();

  const uint8_t max = 20;
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
  for (size_t i = 0; i < RGBLED_NUM; ++i)
  {
    LED_TYPE *led_ = (LED_TYPE *)&led[i];
    switch (i % 2)
    {
      case 0:
        setrgb(max, 0, max, led_);
        break;
      case 1:
        setrgb(0, max, max, led_);
        break;
    }
  }
  rgblight_set();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }
  if (keycode == QK_BOOT)
  {
    setupForFlashing();
  }
  return process_record_user(keycode, record);
}

void keyboard_post_init_user(void) {
  debug_enable = true;
  debug_matrix = true;
  rgblight_enable_noeeprom();
  rgblight_sethsv_noeeprom(HSV_MAGENTA);
  rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL);
}
