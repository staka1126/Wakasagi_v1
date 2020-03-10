#include "Wksg.h"

void wksg_SpeedControllerInit() {
  // グローバル変数の初期化
  motor_speed = MOTOR_SPEED_DEFAULT;
}

void wksg_SpeedControllerStateMachine(int event) {
  switch(event) {
  case EVENT_FALLING_EDGE:
    break;
  case EVENT_RISING_EDGE:
    if (motor_speed < MOTOR_SPEED_MAXIMUM) {
      motor_speed++;
      wksg_LogWrite(MODULE_SPEED_CONTROLLER, String("changed motor speed(" + String(motor_speed) + ")."));
    }
    break;
  case EVENT_KEY_REPEAT:
    if (motor_speed > MOTOR_SPEED_MINIMUM) {
      motor_speed--;
      wksg_LogWrite(MODULE_SPEED_CONTROLLER, String("changed motor speed(" + String(motor_speed) + ")."));
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
  ledcWrite(PWM_CHANNEL, 205 + motor_speed * 10);
}
