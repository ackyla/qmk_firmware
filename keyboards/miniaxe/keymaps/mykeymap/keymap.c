/* Copyright 2018 ENDO Katsuhiro <ka2hiro@curlybracket.co.jp>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

// Defines the keycodes used by our macros in process_record_user
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

#define LW_LANG LT(LOWER, KC_MHEN)
#define RS_LANG LT(RAISE, KC_HENK)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   Q  |   W  |   E  |   R  |   T  |           |   Y  |   U  |   I  |   O  |   P  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   A  |   S  |   D  |   F  |   G  |           |   H  |   J  |   K  |   L  |   ;  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |   Z  |   X  |   C  |   V  |   B  |           |   N  |   M  |   ,  |   .  |   /  |
 * `-------------+------+------+------|           |------+------+------+------+------'
 *               | GUI  |Lower/E|Ctrl/Enter|      |Sft/Spc|Raise/J|Alt/BkSp |
 *               `--------------------'           `--------------------'
 */
[_QWERTY] = LAYOUT( \
  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    \
  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, \
  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,         KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, \
                    KC_LGUI, LW_LANG, MT(MOD_LCTL, KC_ENT),   MT(MOD_LSFT, KC_SPC), RS_LANG, MT(MOD_LALT, KC_BSPC)  \
),

/* Lower
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   !  |   @  |   #  |   $  |   %  |           |   ^  |   &  |   *  |   (  |   )  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Tab |      |      |      |      |           |   "  |   _  |   +  |   {  |   }  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |      |      |      |      |      |           |      |      |      |   ~  |   |  |
 * `-------------+------+------+------|           |------+------+------+------+------'
 *               |      | LOWER|      |           |      | RAISE|      |
 *               `--------------------'           `--------------------'
 */
[_LOWER] = LAYOUT( \
  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, \
  KC_TAB,  _______, _______, _______, _______,      KC_DQUO, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, \
  _______, _______, _______, _______, _______,      _______, _______, _______, KC_TILD, KC_PIPE, \
                    _______, _______, _______,      _______, _______, _______\
),

/* Raise
 *
 * ,----------------------------------.           ,----------------------------------.
 * |   1  |   2  |   3  |   4  |   5  |           |   6  |   7  |   8  |   9  |   0  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |  Tab |      |      |      |      |           |   '  |   -  |   =  |   [  |   ]  |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |      |   `  |      |      |      |           |      |      |      |   `  |   \  |
 * `-------------+------+------+------|           |------+------+------+------+------'
 *               |      | LOWER|      |           |      | RAISE|      |
 *               `--------------------'           `--------------------'
 */
[_RAISE] = LAYOUT( \
  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    \
  KC_TAB,  _______, _______, _______, _______,      KC_QUOT, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, \
  _______, _______, _______, _______, _______,      _______, _______, _______, KC_GRV,  KC_BSLS, \
                    _______, _______, _______,      _______, _______, _______                    \
),


/* Adjust (Lower + Raise)
 *
 * ,----------------------------------.           ,----------------------------------.
 * |  Esc |      |      |      |      |           |      |      |      |  Up  |      |
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |      |      |      |      |      |           |      |      | Left | Down | Right|
 * |------+------+------+------+------|           |------+------+------+------+------|
 * |      |      |      |      |      |           |      |      |      |      |      |
 * `-------------+------+------+------|           |------+------+------+------+------'
 *               |      | LOWER|      |           |      | RAISE|      |
 *               `--------------------'           `--------------------'
 */
[_ADJUST] =  LAYOUT( \
  KC_ESC,   _______,  _______, _______, _______,      _______, _______, _______,   KC_UP, _______, \
  _______,  _______,  _______, _______, _______,      _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, \
  _______,   _______, _______, _______, _______,      _______, _______, _______, _______, _______, \
                      _______, _______, _______,      _______, _______, _______                   \
)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        // persistant_default_layer_set(1UL<<_QWERTY);
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

void led_set_user(uint8_t usb_led) {
}
