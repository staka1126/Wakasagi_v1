/**
 * @file Wksg.h
 * @brief ワカサギ用電動リールの各モジュールからのログを出力するモジュール
 * @author staka1126@gmail.com
 * @date 2020/03/10
 */
#include "Wksg.h"

void wksg_LogInit(void){
  // グローバル変数の初期化

  // デバイスの初期化
  Serial.begin(115200);
}

void wksg_LogWrite(int module_id, String str){
  if (log_settings[module_id].onoff) {
    Serial.println(String("[") + String(millis()) + String("]") + log_settings[module_id].module_name + ":" + str);
  }
}
