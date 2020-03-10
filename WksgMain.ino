#include "Wksg.h"

void setup() {
  // put your setup code here, to run once:
  wksg_LogInit();                             // ログシステムの初期化
  wksg_TimerInit();                           // タイマーの初期化
  wksg_EepromInit();                          // 保存データの復帰
  wksg_KeyInit();                             // KEYの初期化
  wksg_CounterInit();                         // わかさぎカウンターの初期化
  wksg_MotorInit();                           // モーターの初期化（SpeedControllerより先に初期化が必要）
  wksg_SpeedControllerInit();                 // スピードコントローラの初期化
  wksg_DisplayInit();                         // SSD1306と表示の初期化
}

void loop() {
  // put your main code here, to run repeatedly:
  wksg_KeyCheck();                            // キー入力の検出
  wksg_Dispatcher();                          // キーイベント処理
  wksg_TimerUpdate();                         // タイマーイベント処理
  if (dirty) {
    wksg_DisplayUpdate(EVENT_DISPLAY_ON);     // 表示の更新
    dirty = false;
  }
  delay(DISPATCH_PERIOD);                     // 時間調整
}
