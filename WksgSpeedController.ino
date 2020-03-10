/**
 * @file Wksg.h
 * @brief ワカサギ用電動リールのモーター回転速度をするモジュール
 * @author staka1126@gmail.com
 * @date 2020/03/10
 */
#include "Wksg.h"

void wksg_SpeedControllerInit() {
  // グローバル変数の初期化
  if (!((MOTOR_SPEED_MINIMUM <= save_data.motor_speed) && (save_data.motor_speed <= MOTOR_SPEED_MAXIMUM))) {    // 保存データの妥当性チェック
    save_data.motor_speed = MOTOR_SPEED_DEFAULT;      // 不正な値だった場合はデフォルトにする
  }
}

void wksg_SpeedControllerStateMachine(int event) {
  switch(event) {
  case EVENT_FALLING_EDGE:
    break;
  case EVENT_RISING_EDGE:
    if (save_data.motor_speed < MOTOR_SPEED_MAXIMUM) {
      save_data.motor_speed++;
      wksg_LogWrite(MODULE_SPEED_CONTROLLER, String("changed motor speed(" + String(save_data.motor_speed) + ")."));
    }
    break;
  case EVENT_KEY_REPEAT:
    if (save_data.motor_speed > MOTOR_SPEED_MINIMUM) {
      save_data.motor_speed--;
      wksg_LogWrite(MODULE_SPEED_CONTROLLER, String("changed motor speed(" + String(save_data.motor_speed) + ")."));
    }
    break;
  case EVENT_LONG_PRESS:
    break;
  default:
    break;
  }
  wksg_SpeedControllerUpdate();
}

void wksg_SpeedControllerUpdate() {
  ledcWrite(PWM_CHANNEL, 205 + save_data.motor_speed * 10);
}
