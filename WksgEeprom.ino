/**
 * @file Wksg.h
 * @brief ワカサギ用電動リールのデータを読出し・書き込みを行うモジュール
 * @author staka1126@gmail.com
 * @date 2020/03/10
 */
#include "Wksg.h"
#include "EEPROM.h"

void wksg_EepromInit() {
  save_data_timer = SAVE_DATA_PERIOD;
  EEPROM.begin(sizeof(SAVE_DATA));
  EEPROM.get<SAVE_DATA>(0, save_data);
  wksg_LogWrite(MODULE_EEPROM, String("read wakasagi_counter = " + String(save_data.wakasagi_counter)));
  wksg_LogWrite(MODULE_EEPROM, String("read motor_speed = " + String(save_data.motor_speed)));
}

void wksg_EepromSave(int event) {
  switch(event) {
  case EVENT_SAVE_DATA:
    save_data_timer = SAVE_DATA_PERIOD;
    EEPROM.put<SAVE_DATA>(0, save_data);
    EEPROM.commit();
    wksg_LogWrite(MODULE_EEPROM, String("save data."));
    break;
  default:
    break;
  }
}
