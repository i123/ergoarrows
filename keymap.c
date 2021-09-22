/*
Copyright 2021 Salicylic_Acid

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

static uint32_t key_timer = 0;
static bool key_trigger = true;

// キーボード初期化後に呼ばれる関数
void keyboard_post_init_user(void) {
   //// LED発光を無効
   int i;
	for (i = 0; i <= 11; i++){
		rgblight_sethsv_at(HSV_BLACK, i);
	}
} 

// マクロキーコードの定義
enum custom_keycodes {
    HOGE = SAFE_RANGE,
	KEY_TIM,
};

// マクロ記述箇所
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
		case HOGE:
			if (record->event.pressed) {
				// when keycode HOGE is pressed
				SEND_STRING("https://qmk.fm/\n");
				SEND_STRING(SS_TAP(X_ENTER));
			} else {
				// when keycode HOGE is released
			}
			break;
        case KEY_TIM:
            if (record->event.pressed) {
                key_trigger ^= true;
				// 機能のON/OFF LEDで表示
				if (key_trigger) {
					rgblight_sethsv_at(HSV_RED, 11);    
				}else{
					rgblight_sethsv_at(HSV_GREEN, 11);  
				}
            }
			break; 	
    }
    return true;
}

void matrix_scan_user(void) { 
	// スクリーンセーバ抑止
    if (timer_elapsed32(key_timer) > 30000) { // 30 seconds
        key_timer = timer_read32();  // resets timer
        if (key_trigger) {
			tap_code(KC_MS_UP);
			tap_code(KC_MS_DOWN);
		}else{
		}
	}
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
  //,--------------------------------------------------------------|   |--------------------------------------------------------------.
       KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,        KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+-----------------|   |--------+--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,        KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSLS,
  //|--------+--------+--------+--------+--------+-----------------|   |--------+--------+--------+--------+--------+--------+--------|
      KC_CAPS,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,        KC_G,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,  KC_ENT,
  //|--------+--------+--------+--------+--------+-----------------|   |--------+--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,        KC_B,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
  //|--------+--------+--------+--------+--------+-----------------|   |--------+--------+--------+--------+--------+--------+--------|
     KC_LCTRL, KC_LGUI,   KC_UP, KC_LALT, KC_MHEN, LT(1, KC_SPC),  KC_DEL,     KC_BSPC,  KC_DEL,  KC_SPC, KC_RALT,   KC_UP,  KC_APP, MO(1),
  //|--------+--------+--------+--------+--------+-----------------|   |--------+--------+--------+--------+--------+--------+--------|
               KC_LEFT, KC_DOWN, KC_RGHT,                                                           KC_LEFT, KC_DOWN, KC_RGHT    
  //|--------------------------------------------------------------|   |--------------------------------------------------------------'
  ),

  [1] = LAYOUT(
  //,--------------------------------------------------------------|   |--------------------------------------------------------------.
       KC_GRV,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,       KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, KC_PSCR,
  //|--------+--------+--------+--------+--------+-----------------|   |--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, KC_PSCR, KC_SLCK, KC_LBRC, KC_RBRC,
  //|--------+--------+--------+--------+--------+-----------------|   |--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, KC_HOME, KC_PGUP, KC_QUOT, _______,
  //|--------+--------+--------+--------+--------+-----------------|   |--------+--------+--------+--------+--------+--------+--------|
      _______, RGB_TOG, RGB_MOD, _______, RGB_SAD, RGB_SAI, _______,     _______, _______, _______,  KC_END, KC_PGDN, _______, _______,
  //|--------+--------+--------+--------+--------+-----------------|   |--------+--------+--------+--------+--------+--------+--------|
      _______, RGB_VAD, KC_VOLU, RGB_VAI, RGB_HUD, RGB_HUI, _______,     _______, _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+-----------------|   |--------+--------+--------+--------+--------+--------+--------|
               KC_MPRV, HOGE   , KEY_TIM,                                                           _______, _______, _______    
  //|--------------------------------------------------------------|   |--------------------------------------------------------------'
  ),

  [2] = LAYOUT(
  //,--------------------------------------------------------------|   |--------------------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+-----------------|   |--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+-----------------|   |--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+-----------------|   |--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+-----------------|   |--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+-----------------|   |--------+--------+--------+--------+--------+--------+--------|
               XXXXXXX, XXXXXXX, XXXXXXX,                                                           XXXXXXX, XXXXXXX, XXXXXXX    
  //|--------------------------------------------------------------|   |--------------------------------------------------------------'
  ),
};


