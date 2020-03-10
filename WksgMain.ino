#include "Wksg.h"

void setup() {
  // put your setup code here, to run once:
  wksg_LogInit();
  wksg_KeyInit();
  wksg_CounterInit();
  wksg_MotorInit();                           // SpeedControllerより先に初期化が必要
  wksg_SpeedControllerInit();
  wksg_DisplayInit();
}

void loop() {
  // put your main code here, to run repeatedly:
  wksg_KeyCheck();                            // キー入力の検出
  wksg_Dispatcher();                          // キーイベント処理
  wksg_TimerManager();                        // タイマーイベント処理
  if (dirty) {
    wksg_DisplayUpdate(EVENT_DISPLAY_ON);     // 表示の更新
    dirty = false;
  }
  delay(DISPATCH_PERIOD); 
}
