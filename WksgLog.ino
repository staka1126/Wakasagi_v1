/**
 * @file Wksg.h
 * @brief ワカサギ用電動リールの各モジュールからのログを出力するモジュール
 * @author staka1126@gmail.com
 * @date 2020/03/10
 */
#include "Wksg.h"
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void wksg_LogInit(void){
  // グローバル変数の初期化

  // デバイスの初期化
  Serial.begin(115200);
  SerialBT.begin("ESP32_Wksg"); //Bluetooth device name
}

void wksg_LogWrite(int module_id, String str){
  if (log_settings[module_id].onoff) {
    Serial.println(String("[") + String(millis()) + String("]") + log_settings[module_id].module_name + ":" + str);
    SerialBT.println(String("[") + String(millis()) + String("]") + log_settings[module_id].module_name + ":" + str);
  }
}
