/**
 * @file Wksg.h
 * @brief ワカサギ用電動リールのタイマーイベントを発生させるモジュール
 * @author staka1126@gmail.com
 * @date 2020/03/10
 */
#include "Wksg.h"

void wksg_TimerInit() {
  
}

void wksg_TimerUpdate() {
  static int time_diff;
  static int time_old = 0;

  time_diff = millis() - time_old;
  time_old = millis();
  
  //-----------------------------------------------------
  // なんちゃってタイマーイベント（ベタ書きしてください）
  //-----------------------------------------------------
  // ちょい巻タイマーイベント
  if (cyoimaki_timer > 0) {
    cyoimaki_timer -= time_diff;
    if (cyoimaki_timer <= 0) {
      wksg_MotorStateMachine(EVENT_CYOIMAKI_STOP);
      dirty = true;
    }
  }

  // ディスプレイOFFタイマーイベント
  if (display_timer > 0) {
    display_timer -= time_diff;
    if (display_timer <= 0) {
      wksg_DisplayUpdate(EVENT_DISPLAY_OFF);
//      dirty = true;
    }
  }

  // データ保存用周期タイマー
  if (save_data_timer > 0) {
    save_data_timer -= time_diff;
    if (save_data_timer <= 0) {
      wksg_EepromSave(EVENT_SAVE_DATA);
    }
  }
}
