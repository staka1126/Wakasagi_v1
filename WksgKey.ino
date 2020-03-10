/**
 * @file Wksg.h
 * @brief ワカサギ用電動リールの押しボタンの検出を行うモジュール
 * @author staka1126@gmail.com
 * @date 2020/03/10
 */
#include "Wksg.h"

void wksg_KeyInit(){
  // グローバル変数の初期化

  // デバイスの初期化
  for (int i = 0; i < sizeof(sw)/sizeof(SWITCH); i++) {
    pinMode(sw[i].port, sw[i].setting);
  }
}

void wksg_KeyCheck(){
  for (int i = 0; i < sizeof(sw)/sizeof(SWITCH); i++) {
      sw[i].old = sw[i].now;
      sw[i].now = digitalRead(sw[i].port);
      
      if (sw[i].old && !sw[i].now) {
        sw[i].event = EVENT_FALLING_EDGE;
        sw[i].press_start = millis();    // timer start
        sw[i].repeat_start = millis();    // timer start
        wksg_LogWrite(MODULE_KEY, String("detected falling edge port" + String(sw[i].port) + ".[" + String(sw[i].name) + "(" + String(sw[i].id) + ")]"));
      }
      else if (!sw[i].old && sw[i].now) {
        if (millis() - sw[i].press_start > LONG_PRESS_THRESHHOLD) {
          sw[i].event = EVENT_LONG_PRESS;
          sw[i].press_start = 0;    // reset
          sw[i].repeat_start = 0;   // reset
          wksg_LogWrite(MODULE_KEY, String("detected long press port" + String(sw[i].port) + ".[" + String(sw[i].name) + "(" + String(sw[i].id) + ")]"));
        }
        else{
          sw[i].event = EVENT_RISING_EDGE;
          sw[i].press_start = 0;    // reset
          sw[i].repeat_start = 0;   // reset
          wksg_LogWrite(MODULE_KEY, String("detected raising edge port" + String(sw[i].port) + ".[" + String(sw[i].name) + "(" + String(sw[i].id) + ")]"));
        }
      }
      else if (!sw[i].old && !sw[i].now) {
        if ((millis() - sw[i].repeat_start > LONG_PRESS_THRESHHOLD) && (sw[i].event != EVENT_RISING_EDGE) && (sw[i].event != EVENT_LONG_PRESS)) {
          sw[i].event = EVENT_KEY_REPEAT;
          sw[i].repeat_start = millis();
          wksg_LogWrite(MODULE_KEY, String("detected key repeat port" + String(sw[i].port) + ".[" + String(sw[i].name) + "(" + String(sw[i].id) + ")]"));
        }
      }
      else{
        sw[i].press_start = 0;    // reset
        sw[i].repeat_start = 0;    // reset
      }
  }
}
