// Copyright 2023 John Barbero Unenge (@jbarberu)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum Layer {
    L_Numpad = 0,
    L_Symbols,
    L_EasyEDA,
    L_RGB,
    L_Adjust
};

enum CustomKeyCodes
{
    CC_DADT = SAFE_RANGE,
    CC_DADN
};

static bool showJoke = false;
static const char* currentJoke = "";
static const char* jokes[] = {
"What do you call an  "
"old snowman?         "
"Water.",

"Shout out to my gran,"
"it's the only way she"
"can hear.",

"I couldn't figure out"
"the seat belt.       "
"Then it just clicked.",

"Geology rocks, but   "
"Geography is where it"
"is at!               ",

"I just broke my      "
"guitar. It's okay, I "
"won't fret.          ",

"I'm glad I know sign "
"language, it's pretty"
"handy.               ",

"- What time is it?   "
"- I don't know... it "
"keeps changing.      ",

"The rotation of earth"
"really makes my day. ",

"I'm reading a book on"
"the history of glue  "
"- can't put it down. ",

"- I'm sorry.         "
"- Hi sorry, I'm dad. ",

"The US can't switch  "
"from pounds to grams "
"overnight. That would"
"cause mass confusion.",

"I told my friend 10  "
"puns hoping one would"
"crack him up. Sadly, "
"no pun in ten did.   ",

"How come the stadium "
"got hot after the    "
"game? Because all of "
"the fans left.       ",

"My sea sickness comes"
"in waves.            ",

"My boss told me to   "
"have a good day. So I"
"went home...",

"Hear about the new   "
"restaurant, Karma?   "
"There's no menu - You"
"get what you deserve."
};

// clang-format off
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
      KC_P7,   KC_P8,   KC_P9,       TO(L_EasyEDA)
    , KC_P4,   KC_P5,   KC_P6,       LT(L_Symbols, KC_PCMM)
    , KC_P1,   KC_P2,   KC_P3,       KC_P0

    , KC_A,    KC_S,    KC_ENT,      KC_BSPC
    , KC_UP,   KC_DOWN, KC_LEFT,     KC_RIGHT
    , KC_X,    KC_Z,    LSFT(KC_F1), KC_TAB
  ),
  [L_EasyEDA] = LAYOUT(
      KC_COMM, KC_DOT,  KC_K,    TO(L_RGB)
    , KC_LSFT, KC_M,    KC_N,    TO(L_Numpad)
    , KC_LCTL, KC_SPC,  KC_DEL,  KC_BSPC

    , KC_A,    KC_B,    KC_C,    KC_D
    , QK_BOOT, KC_TRNS, KC_G,    KC_H
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
    , KC_NUM,  CC_DADT, CC_DADN, QK_BOOT

    , KC_A,    KC_B,    KC_C,    KC_D
    , KC_E,    KC_F,    KC_G,    KC_H
    , KC_I,    KC_J,    KC_K,    KC_L
  )
};
// clang-format on

const char * get_layer_name_user(uint8_t layer) {
    switch (layer) {
        case L_Numpad:
            return "Numpad";
        case L_EasyEDA:
            return "EasyEDA";
        case L_RGB:
            return "RGB Controls";
        case L_Adjust:
            return "Adjust";
        case L_Symbols:
            return "Symbols";
        default:
            return "Undef";
    }
}

bool oled_task_user(void)
{
    if (showJoke)
    {
        oled_clear();
        oled_write(currentJoke, false);
        oled_render_dirty(true);
    }
    return !showJoke;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode)
        {
            case CC_DADT:
                showJoke = !showJoke;
                return false;
            case CC_DADN:
                currentJoke = jokes[rand() % (sizeof(jokes) / sizeof(const char*))];
                return false;
        }
    }
    return true;
}
