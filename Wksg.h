#ifndef INCLUDE_WAKASAGI_H
#define INCLUDE_WAKASAGI_H

//==============================================================================
// 定義
//==============================================================================
// SWITCH GPIO定義・変数
#define LONG_PRESS_THRESHHOLD   (500)    // ms

// Keyの監視周期(ms)
#define DISPATCH_PERIOD     (10)

// Speed Controller用定義・変数
#define MOTOR_SPEED_DEFAULT (3)
#define MOTOR_SPEED_MINIMUM (1)
#define MOTOR_SPEED_MAXIMUM (5)

// PORT定義
#define PORT_SW01           (26)
#define PORT_SW02           (27)
#define PORT_SW03           (32)
#define PORT_SW04           (33)
#define PORT_MOTOR_SPEED    (4)
#define PORT_MOTOR_IN01     (17)
#define PORT_MOTOR_IN02     (16)

#define MOTOR_SPEED_VARIABLE  true

// ちょい巻時間(ms)
#define CYOIMAKI_TIMER_INIT (1000)

// DISP OFF時間(ms)
#define DISPLAY_TIMER_INIT  (5000)

//==============================================================================
// 構造体
//==============================================================================
struct SWITCH {
  word port;
  int id;
  char name[20];
  int setting;
  boolean now;
  boolean old;
  unsigned long press_start;
  unsigned long repeat_start;
  int event; 
};

struct LOG {
  char module_name[20];
  boolean onoff;
};

//==============================================================================
// enum値
//==============================================================================
// LOGの設定
enum {
  MODULE_KEY = 0,
  MODULE_DISPATCHER,
  MODULE_SPEED_CONTROLLER,
  MODULE_COUNTER,
  MODULE_MOTOR,
  MODULE_DISPLAY,
  MODULE_MAX
};

// KEY定義
enum {
  KEY_NULL = 0,
  KEY_SPEED,
  KEY_COUNTER,
  KEY_MOTOR,
  KEY_STOP,
  KEY_RESET,
  KEY_MAX,
};

// EVENT定義
enum {
  EVENT_NULL = 0,
  EVENT_FALLING_EDGE,
  EVENT_KEY_REPEAT,
  EVENT_RISING_EDGE,
  EVENT_LONG_PRESS,
  EVENT_CYOIMAKI_STOP,
  EVENT_DISPLAY_ON,
  EVENT_DISPLAY_OFF,
  EVENT_MOTOR_STOP,
  EVENT_MAX
};

//==============================================================================
// グローバル変数
//==============================================================================
// KEYの設定
SWITCH sw[] = {
  {PORT_SW01, KEY_SPEED, "speed", INPUT_PULLUP, true, true, 0, EVENT_NULL},
  {PORT_SW02, KEY_COUNTER, "counter", INPUT_PULLUP, true, true, 0, EVENT_NULL},
  {PORT_SW03, KEY_MOTOR, "motor", INPUT_PULLUP, true, true, 0, EVENT_NULL},
  {PORT_SW04, KEY_STOP, "null", INPUT_PULLUP, true, true, 0, EVENT_NULL},
};

// ログの設定（enumと順序関係が連動しています）
LOG log_settings[] = {
  {"key", false},                 // MODULE_KEY
  {"dispatcher", true},           // MODULE_DISPATCHER
  {"speed controller", true},     // MODULE_SPEED_CONTROLLER
  {"counter", true},              // MODULE_COUNTER
  {"motor", true},                // MODULE_MOTOR
  {"ssd1306", true}               // MODULE_DISPLAY
};

// ワカサギの数
int wakasagi_counter = 0;

// モーター速度
int motor_speed = MOTOR_SPEED_DEFAULT;

// モーターの回転状態
boolean motor_status = false;

// ちょい巻用のなんちゃってタイマー割り込み
int cyoimaki_timer = 0;

// ディスプレイ消灯用のなんちゃってタイマー割り込み
int display_timer = 0;

// 表示更新用のフラグ
boolean dirty = true;

#endif
