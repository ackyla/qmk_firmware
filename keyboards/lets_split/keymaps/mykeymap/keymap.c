#include "lets_split.h"
#include "action_layer.h"
#include "eeconfig.h"
#ifdef CONSOLE_ENABLE
#include <print.h>
#endif

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _MEDIA 3
#define _KB 4

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
	MEDIA,
	KB,
	AU_KEY_UP,
	AU_KEY_DOWN,
	VOI_M_DF, // default_voice
	VOI_M_SM, // something
	VOI_M_BF, // butts_fader
	VOI_M_DO, // duty_osc
	VOI_M_DOD, // duty_octave_down
	VOI_M_DV, // delayed_vibrato
	CHROM_TOG
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define LW_LANG LT(_LOWER,KC_LANG2)
#define RS_LANG LT(_RAISE,KC_LANG1)
#define SFT_QT MT(MOD_RSFT,KC_QUOT)

#ifdef RGBLIGHT_ENABLE
extern rgblight_config_t rgblight_config;
#endif

// uint8_t base_key = 0x00EC;
uint8_t base_key = 228;
bool chromatic_mode = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,------------------------------------------------------------------------------------.
 * | Tab   |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |-------+------+------+------+------+-------------+------+------+------+------+------|
 * | Ctrl  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |enter |
 * |-------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |'/sft |
 * |-------+------+------+------+------+------+------+------+------+------+------+------|
 * |   KB  |Media | ALT  |  GUI |LowerJ|Space |Space |RaiseE| Left | Down |  Up  |Right |
 * `------------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_4x12( \
  KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC, \
  KC_LCTL,  KC_A,    KC_S,    KC_D,    KC_F,   KC_G,   KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  KC_ENT, \
  KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,   KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  SFT_QT, \
  DF(_KB), MO(_MEDIA), KC_LALT, KC_RGUI, LW_LANG, KC_SPC, KC_SPC, RS_LANG, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_4x12( \
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, \
  _______, _______, _______, _______, _______, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_ortho_4x12( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  _______, _______, _______, _______, _______, _______, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
),

/* Media
 * ,-----------------------------------------------------------------------------------.
 * | ESC  |Mbtn2 |  Mup |Mbtn1 |      |      |  F6  |  F7  |  F8  |  F9  |      | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |Mleft |Mdown |Mright|      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |SOUND |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MEDIA] = LAYOUT_ortho_4x12( \
  KC_ESC,  KC_BTN2, KC_MS_U, KC_BTN1, _______, _______,   KC_F6,   KC_F7,   KC_F8,   KC_F9, _______, KC_BSPC, \
  _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, RGB_HUI, RGB_SAI, RGB_VAI, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, RGB_HUD, RGB_SAD, RGB_VAD, RGB_M_X, RGB_M_G, _______, \
  CHROM_TOG, _______, _______, _______, _______, _______, RGB_M_P, RGB_M_B, RGB_M_R,RGB_M_SW,RGB_M_SN, RGB_M_K \
),

[_KB] = LAYOUT_ortho_4x12( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_M_X, RGB_M_G, XXXXXXX, \
	DF(_QWERTY), XXXXXXX, XXXXXXX, XXXXXXX, AU_KEY_DOWN, AU_KEY_UP, VOI_M_DF, VOI_M_SM, VOI_M_BF, VOI_M_DO, VOI_M_DOD,VOI_M_DV \
)

};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

uint32_t layer_state_set_user(uint32_t state) {
#ifdef RGBLIGHT_ENABLE
	uint16_t val;
	if (rgblight_config.val == 0) {
		val = 100;
	} else {
		val = rgblight_config.val;
	}
	switch (biton32(state)) {
	case _RAISE:
		rgblight_enable();
		rgblight_sethsv(0, 255, val);
		break;
	case _LOWER:
		rgblight_enable();
		rgblight_sethsv(240, 255, val);
		break;
	case _MEDIA:
		rgblight_enable();
		rgblight_sethsv(120, 255, val);
		break;
	default:
		rgblight_disable();
		break;
	}
#endif
	return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef AUDIO_ENABLE
	uint8_t note;
	int col;
	int row;
	if(record->event.key.row >= MATRIX_ROWS / 2) {
		col = MATRIX_COLS * 2 - record->event.key.col - 1;
		row = record->event.key.row - MATRIX_ROWS / 2;
	} else {
		col = record->event.key.col;
		row = record->event.key.row;
	}
	note = (base_key + col + 7 - 3)+12*(MATRIX_ROWS - row);
	if (record->event.pressed) {
		if (chromatic_mode) {
			process_audio_noteon(note);
		} else {
			if(row < 3) {
				process_audio_noteon(note);
			}
		}
		if (keycode == CHROM_TOG) {
			if (chromatic_mode) {
				chromatic_mode = false;
				audio_off();
			} else {
				chromatic_mode = true;
				audio_on();
			}
		}
		if (keycode == DF(_KB)) {
			uint16_t val;
			chromatic_mode = false;
			if (rgblight_config.val == 0) {
				val = 100;
			} else {
				val = rgblight_config.val;
			}
			rgblight_enable();
			rgblight_sethsv(255, 0, val);
			audio_on();
		}
		if (keycode == DF(_QWERTY)) {
			rgblight_disable();
			audio_off();
		}
		switch (keycode) {
		case AU_KEY_UP:
			if(base_key < 252) {
				base_key += 24;
			}
			return false;
			break;
		case AU_KEY_DOWN:
			base_key -= 24;
			if(base_key < 204) {
				base_key = 204;
			}
			return false;
			break;
		case VOI_M_DF:
			set_voice(0);
			return false;
			break;
		case VOI_M_SM:
			set_voice(1);
			return false;
			break;
		case VOI_M_BF:
			set_voice(3);
			return false;
			break;
		case VOI_M_DO:
			set_voice(5);
			return false;
			break;
		case VOI_M_DOD:
			set_voice(6);
			return false;
			break;
		case VOI_M_DV:
			set_voice(7);
			return false;
			break;
		}
	} else {
		process_audio_noteoff(note);
	}
#endif
  return true;
}
