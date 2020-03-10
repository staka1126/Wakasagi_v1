#include "Wksg.h"

void wksg_CounterInit() {
  // グローバル変数の初期化
  if (!((0 <= save_data.wakasagi_counter) && (save_data.wakasagi_counter <= 9999))) {    // 保存データの妥当性チェック
    save_data.wakasagi_counter = 0;      // 不正な値だった場合はゼロクリアする
  }
}

void wksg_CounterStateMachine(int event) {
  switch(event) {
  case EVENT_FALLING_EDGE:
    break;
  case EVENT_RISING_EDGE:
    save_data.wakasagi_counter++;
    wksg_LogWrite(MODULE_COUNTER, String("wakasagi count up(" + String(save_data.wakasagi_counter) + ")."));
    break;
  case EVENT_KEY_REPEAT:
    static int tmp = 0;
    static int minus = 1;
    if (save_data.wakasagi_counter > 0) {
      if (tmp < 10) {
        save_data.wakasagi_counter--;
        tmp++;
        wksg_LogWrite(MODULE_COUNTER, String("wakasagi count down(" + String(save_data.wakasagi_counter) + ")."));
      }
      else {    // 10匹以上からは1ずつ減少量をスピードアップ
        save_data.wakasagi_counter -= minus;
        if (save_data.wakasagi_counter < 0) {
          save_data.wakasagi_counter = 0;     // 引きすぎたらゼロに戻す
          wksg_EepromSave(EVENT_SAVE_DATA);   // データ保存（特別処理）
        }
        tmp++;
        minus++;
        wksg_LogWrite(MODULE_COUNTER, String("wakasagi count down(" + String(save_data.wakasagi_counter) + ")."));
      }
    }
    break;
  case EVENT_LONG_PRESS:
    break;
  default:
    break;
  }
}
