/**
 * @file Wksg.h
 * @brief ワカサギ用電動リールのモーターのスタート・ストップを制御するモジュール
 * @author staka1126@gmail.com
 * @date 2020/03/10
 */
#include "Wksg.h"


void wksg_MotorInit() {
  // グローバル変数の初期化

  // デバイスの初期化
  pinMode(PORT_MOTOR_SPEED, OUTPUT);
  pinMode(PORT_MOTOR_IN01, OUTPUT);
  pinMode(PORT_MOTOR_IN02, OUTPUT);
  ledcSetup(PWM_CHANNEL,12800,8); 
  ledcAttachPin(PORT_MOTOR_SPEED,PWM_CHANNEL);
}

void wksg_MotorStateMachine(int event) {
  switch(event) {
  case EVENT_FALLING_EDGE:
    wksg_MotorStart();
    break;
  case EVENT_RISING_EDGE:
    wksg_MotorCyoimakiStart();
    wksg_LogWrite(MODULE_MOTOR, String("cyoimaki start."));
    break;
  case EVENT_KEY_REPEAT:
    break;
  case EVENT_LONG_PRESS:
  case EVENT_CYOIMAKI_STOP:
  case EVENT_MOTOR_STOP:
    wksg_MotorStop();
    break;
  default:
    break;
  }
}

void wksg_MotorStart() {
  wksg_LogWrite(MODULE_MOTOR, String("motor start(speed:" + String(save_data.motor_speed) + ")."));
  digitalWrite(PORT_MOTOR_IN01, HIGH);
  digitalWrite(PORT_MOTOR_IN02, LOW);
  motor_status = true;
}

void wksg_MotorCyoimakiStart() {
  cyoimaki_timer = CYOIMAKI_TIMER_INIT;
}

void wksg_MotorStop() {
  wksg_LogWrite(MODULE_MOTOR, String("motor stop."));
  digitalWrite(PORT_MOTOR_IN01, LOW);
  digitalWrite(PORT_MOTOR_IN02, LOW);
  motor_status = false;
}
