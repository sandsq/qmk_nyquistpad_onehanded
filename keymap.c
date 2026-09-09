/* Copyright 2018 MechMerlin
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

enum layers {
    _MAIN,
    _ALPHA2,
    _NUM,
    _UTILS,
};


#define CTRLC LCTL(KC_C)
#define CTRLV LCTL(KC_V)
#define CTRLX LCTL(KC_X)
#define CTRLS LCTL(KC_S)
#define CTRLZ LCTL(KC_Z)
#define OSSFT OSM(MOD_LSFT)
#define OSCTL OSM(MOD_LCTL)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


  /*
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+-----------------+--------+--------|--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'

*/


 [_MAIN] = LAYOUT(
     KC_QUOT,     KC_Y,     KC_U,   OSSFT,     KC_W,   KC_DOT,
       KC_V,     KC_D,     KC_A,   OSL(_ALPHA2),     KC_N,   KC_GRV,
       KC_F,     KC_S,     KC_E,     KC_H,     KC_T,     KC_L,
     OSL(_NUM),     KC_C,     KC_I,     KC_O,     KC_R,     KC_M,
     KC_LGUI,  KC_CAPS,   KC_LALT,  OSL(_UTILS),  KC_BSPC,   KC_SPC
  ),

 [_ALPHA2] = LAYOUT(
     KC_TAB,     KC_J,  KC_SLSH,  _______,   KC_DOT,     KC_Q,
     KC_BSLS,   KC_GRV,     KC_L,  _______,     KC_P,  KC_RBRC,
     OSCTL,     KC_K,     KC_G,  KC_MINS,  KC_COMM,     KC_A,
        KC_Z,     KC_X,  KC_MINS,  _______,  KC_SCLN,  KC_LBRC,
     _______,  _______,  _______,   KC_DOT,     KC_P,     KC_B
  ),

  [_NUM] = LAYOUT(
    KC_LPRN,  KC_RPRN,    KC_EQL,   KC_SLSH,  KC_ASTR,   KC_MINS,
    KC_LBRC,  KC_RBRC,    KC_1,     KC_2,     KC_3,      KC_PLUS,
    KC_LCBR,  KC_RCBR,    KC_4,     KC_5,     KC_6,      KC_ENT,
    _______,  KC_COMM,    KC_7,     KC_8,     KC_9,      KC_UNDS,
    _______,_______,      KC_COLN,  KC_0,     KC_DOT,    OSSFT
  ),

  [_UTILS] = LAYOUT(
    QK_BOOT,  CTRLC,     CTRLV,    CTRLX,    CTRLS,    CTRLZ,
    KC_F1,  KC_F2,     KC_F3,    KC_F4,    KC_F5,    KC_F6,
    _______,  KC_LEFT,   KC_UP,    KC_DOWN,  KC_RIGHT, KC_DEL,
    OSSFT,    KC_HOME,   KC_PGUP,  KC_PGDN,  KC_END,   KC_PSCR,
    KC_F7,  KC_F8,     KC_F9,    _______,    KC_F10,    _______
  ),

};




void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return;
    }

    switch (keycode) {
        case OSSFT:
        case OSCTL:
            clear_oneshot_layer_state(ONESHOT_START);
            break;
    }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) { //|| is_caps_word_on()) {
        RGB_MATRIX_INDICATOR_SET_COLOR(31, 255, 70, 70);
    }

    // int state = 0;
    int hlayer = get_highest_layer(layer_state|default_layer_state);
    bool setlight = false;

    if (hlayer == _ALPHA2) {
        RGB_MATRIX_INDICATOR_SET_COLOR(18, 255, 100, 0);
        setlight = true;
    }
    if (hlayer == _NUM) {
        RGB_MATRIX_INDICATOR_SET_COLOR(29, 153, 255, 51);
        setlight = true;
    }
    if (hlayer == _UTILS) {
        RGB_MATRIX_INDICATOR_SET_COLOR(33, 51, 153, 255);
        setlight = true;
    }
    if (get_oneshot_mods() & MOD_MASK_SHIFT) {
        if (hlayer == _NUM) {
            RGB_MATRIX_INDICATOR_SET_COLOR(35, 102, 0, 204);
            setlight = true;
        } else {
            RGB_MATRIX_INDICATOR_SET_COLOR(2, 102, 0, 204);
            setlight = true;
        }
    }
    if (get_oneshot_mods() & MOD_MASK_CTRL) {
        RGB_MATRIX_INDICATOR_SET_COLOR(15, 102, 50, 204);
        setlight = true;
    }
    if (!setlight) {
        rgb_matrix_sethsv_noeeprom(HSV_OFF);
    }



    return false;
}





void keyboard_post_init_user(void) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(HSV_OFF);
}
