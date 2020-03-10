#include "Wksg.h"

void wksg_CounterInit() {
  // グローバル変数の初期化
  wakasagi_counter = 0;
}

void wksg_CounterStateMachine(int event) {
  switch(event) {
  case EVENT_FALLING_EDGE:
    break;
  case EVENT_RISING_EDGE:
    wakasagi_counter++;
    wksg_LogWrite(MODULE_COUNTER, String("wakasagi count up(" + String(wakasagi_counter) + ")."));
    break;
  case EVENT_KEY_REPEAT:
    if (wakasagi_counter > 0) {
      wakasagi_counter--;
      wksg_LogWrite(MODULE_COUNTER, String("wakasagi count down(" + String(wakasagi_counter) + ")."));
    }
    break;
  case EVENT_LONG_PRESS:
    break;
  default:
    break;
  }
}
