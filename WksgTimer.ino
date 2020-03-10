#include "Wksg.h"

void wksg_TimerManager() {
  static int time_diff;
  static int time_old = 0;

  time_diff = millis() - time_old;
  time_old = millis();
  
  //-----------------------------------------------------
  // なんちゃってタイマーイベント（ベタ書きしてください）
  //-----------------------------------------------------
  // ちょい巻タイマーイベント
  if (cyoimaki_timer > 0) {
    cyoimaki_timer = cyoimaki_timer - time_diff;
    if (cyoimaki_timer <= 0) {
      wksg_MotorStateMachine(EVENT_CYOIMAKI_STOP);
      dirty = true;
    }
  }

  // ディスプレイOFFタイマーイベント
  if (display_timer > 0) {
    display_timer = display_timer - time_diff;
    if (display_timer <= 0) {
      wksg_DisplayUpdate(EVENT_DISPLAY_OFF);
//      dirty = true;
    }
  }
}
