/* Copyright 2024 @ Keychron (https://www.keychron.com)
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
 #include "keychron_common.h"
 
 bool isWinMode;
 
 #ifdef DIP_SWITCH_ENABLE
 bool dip_switch_update_kb(uint8_t index, bool active) {
     if (index == 0) {// OS switch
         default_layer_set(1UL << (active ? 2 : 0));
         isWinMode = active;
     }
     dip_switch_update_user(index, active);
 
     return true;
 }
 #endif
 
 enum layers {
     MAC_BASE,
     MAC_FN,
     WIN_BASE,
     WIN_FN,
     MAC_FN_1,
     GAMING,
 };

 void dance_ins_layers_and_indications(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            tap_code(KC_INS);
            break;
        case 2:
            if (get_highest_layer(layer_state) == GAMING) {
                layer_off(GAMING);
            } else {
                layer_on(GAMING);
            }
            break;
        case 3:
            rgb_matrix_toggle_noeeprom();
            break;
    }
 }
 
 enum tapdances {
     TD_INS_LAI,
 };
 
 tap_dance_action_t tap_dance_actions[] = {
     [TD_INS_LAI] = ACTION_TAP_DANCE_FN(dance_ins_layers_and_indications),
 };
 
 // clang-format off
 const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     [MAC_BASE] = LAYOUT_ansi_90(
         KC_MUTE,    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,        KC_F11,   KC_F12,   TD(TD_INS_LAI),     KC_DEL,
         MC_1,       KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,          KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
         MC_2,       KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,          KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
         MC_3,       KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,      KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,       KC_QUOT,            KC_ENT,             KC_HOME,
         MC_4,       KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,     KC_B,     KC_N,     KC_M,     KC_COMM,       KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,
         MC_5,       KC_LCTL,  KC_LWIN,            KC_LALT,  KC_SPC,   MO(MAC_FN),                    KC_SPC,             MO(MAC_FN_1),  KC_RCTL,            KC_LEFT,  KC_DOWN,  KC_RGHT),
 
     [MAC_FN] = LAYOUT_ansi_90(
         RGB_TOG,    _______,  KC_BRID,  KC_BRIU,  KC_MCTRL, KC_LNPAD, RGB_VAD,   RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  TD(TD_INS_LAI),     NK_TOGG,
         _______,    _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,   _______,  _______,  _______,  _______,  RGB_TOG,  RGB_MOD,  RGB_RMOD, _______,            BAT_LVL,
         _______,    _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
         _______,    _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
         _______,    _______,            _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
         _______,    _______,  _______,            _______,  _______,  _______,                       _______,            _______,  _______,            _______,  _______,  _______),
 
     [WIN_BASE] = LAYOUT_ansi_90(
         KC_MUTE,    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   TD(TD_INS_LAI),     KC_DEL,
         MC_1,       KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
         MC_2,       KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
         MC_3,       KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,      KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,             KC_HOME,
         MC_4,       KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,
         MC_5,       KC_LCTL,  KC_LWIN,            KC_LALT,  KC_SPC,   MO(WIN_FN),                    KC_SPC,             KC_RALT,  KC_RCTL,            KC_LEFT,  KC_DOWN,  KC_RGHT),
 
     [WIN_FN] = LAYOUT_ansi_90(
         RGB_TOG,    _______,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  RGB_VAD,   RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,   KC_VOLU,  TD(TD_INS_LAI),     _______,
         _______,    _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,   _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,            _______,
         _______,    RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,   _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,            TO(GAMING),
         _______,    _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,   _______,  _______,  _______,  _______,  _______,  _______,             _______,            KC_END,
         _______,    _______,            _______,  _______,  _______,  _______,   BAT_LVL,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,   _______,  _______,  _______,
         _______,    _______,  _______,            _______,  _______,  _______,                       _______,            _______,  _______,             _______,  _______,  _______),
 
     [MAC_FN_1] = LAYOUT_ansi_90(
        RGB_TOG,    _______,  KC_BRID,  KC_BRIU,  KC_MCTRL, KC_LNPAD, RGB_VAD,   RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  TD(TD_INS_LAI),     NK_TOGG,
        _______,    _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,   _______,  _______,  _______,  _______,  RGB_TOG,  RGB_MOD,  RGB_RMOD, _______,            BAT_LVL,
        _______,    _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,    _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
        _______,    _______,            _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,    _______,  _______,            _______,  _______,  _______,                       _______,            _______,  _______,            _______,  _______,  _______),
 
     [GAMING] = LAYOUT_ansi_90(
         KC_MUTE,    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   TD(TD_INS_LAI),     KC_DEL,
         MC_1,       KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_LWIN,
         MC_2,       KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            TO(WIN_FN),
         MC_3,       KC_F13,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,      KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,             KC_HOME,
         MC_4,       KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,     KC_F17,   KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,
         MC_5,       KC_LCTL,  KC_F14,             KC_LALT,  KC_SPC,   KC_F15,                        KC_F16,             KC_RALT,  KC_RCTL,            KC_LEFT,  KC_DOWN,  KC_RGHT),
 };
 
 #if defined(ENCODER_MAP_ENABLE)
 const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
     [MAC_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
     [MAC_FN] = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
     [WIN_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
     [WIN_FN] = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
     [MAC_FN_1] = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
     [GAMING] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)}
 };
 #endif // ENCODER_MAP_ENABLE
 
 // clang-format on
 bool process_record_user(uint16_t keycode, keyrecord_t *record) {
     if (!process_record_keychron_common(keycode, record)) {
         return false;
     }
     return true;
 }
 
 bool rgb_matrix_indicators_user(void) {
     uint8_t current_layer = get_highest_layer(layer_state);
     HSV hsvLayerColor = {HSV_BLACK};
 
     switch (current_layer) {
         case WIN_BASE:
         case MAC_BASE:
             if (isWinMode) {
                 hsvLayerColor = (HSV) {HSV_GREEN};
             } else {
                 hsvLayerColor = (HSV) {HSV_AZURE};
             }
             break;
         case MAC_FN:
             hsvLayerColor = (HSV) {HSV_CYAN};
             break;
         case WIN_FN:
             hsvLayerColor = (HSV) {HSV_CORAL};
             break;
         case MAC_FN_1:
             hsvLayerColor = (HSV) {HSV_YELLOW};
             break;
         case GAMING:
             hsvLayerColor = (HSV) {HSV_PURPLE};
             break;
         default:
             break;
     }
 
     hsvLayerColor.v = rgb_matrix_get_val();
     RGB rgbLayerColor = hsv_to_rgb(hsvLayerColor);
 
     rgb_matrix_set_color(81, rgbLayerColor.r, rgbLayerColor.g, rgbLayerColor.b);
     rgb_matrix_set_color(82, rgbLayerColor.r, rgbLayerColor.g, rgbLayerColor.b);
     rgb_matrix_set_color(83, rgbLayerColor.r, rgbLayerColor.g, rgbLayerColor.b);
     rgb_matrix_set_color(84, rgbLayerColor.r, rgbLayerColor.g, rgbLayerColor.b);
 
     return true;
 }
