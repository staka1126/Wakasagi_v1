/**
 * @file Wksg.h
 * @brief ワカサギ用電動リールの表示管理を行うモジュール
 * @author staka1126@gmail.com
 * @date 2020/03/10
 */
#include "Wksg.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

static const unsigned char wakasagi_bmp[] = {
B00000000,B00000000,B00000000,
B00000000,B00000000,B00000000,
B00000000,B00000000,B00001100,
B00000000,B00000000,B00111100,
B00000000,B00000000,B11111100,
B00000000,B00000001,B11111100,
B00000000,B01110011,B11111000,
B00000000,B00111111,B11111000,
B00000000,B00011111,B11110000,
B00000000,B00001111,B11100000,
B00000000,B00011111,B11100000,
B00000000,B00111111,B11000000,
B00000000,B01111111,B10000000,
B00001111,B01111111,B00000000,
B00001111,B11111111,B10000000,
B00000111,B11111111,B10000000,
B00000001,B11111101,B11000000,
B00000011,B11111001,B11000000,
B00000011,B11110001,B11000000,
B00000111,B11100000,B10000000,
B00001111,B10100000,B00000000,
B00011111,B00100000,B00000000,
B00111110,B00000000,B00000000,
B01111110,B00000000,B00000000,
B01101100,B00000000,B00000000,
B00001100,B00000000,B00000000,
B00011000,B00000000,B00000000,
B00010000,B00000000,B00000000,
B00100000,B00000000,B00000000,
B00000000,B00000000,B00000000
};

void wksg_DisplayInit() {
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    wksg_LogWrite(MODULE_DISPLAY, String("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  wksg_LogWrite(MODULE_DISPLAY, String("SSD1306 allocation success."));
  
  // Opening
  wksg_DisplayDrawOpening();
}

void wksg_DisplayDrawOpening() {
  display.clearDisplay();
  // 出力する文字の大きさ
  display.setTextSize(4);
  // 出力する文字の色
  display.setTextColor(WHITE);
  // 文字の一番端の位置
  display.setCursor(0, 0);
  // 出力する文字列
  display.println("Wksg");  
  display.println("Reel!");  
  display.display();
  delay(2000);
}

void wksg_DisplayUpdate(int event) {
  switch(event) {
  case EVENT_DISPLAY_ON:
    display.clearDisplay();
    wksg_DisplayDrawCounter();
    wksg_DisplayDrawMotorSpeed();
    display_timer = DISPLAY_TIMER_INIT;
    break;
  case EVENT_DISPLAY_OFF:
    display.clearDisplay();
    break;
  default:
    break;
  }
  display.display();
}

void wksg_DisplayDrawCounter() {
  display.drawBitmap(4, 2, wakasagi_bmp, 24, 30, 1);
  display.setTextSize(4);
  display.setTextColor(WHITE);
  if (save_data.wakasagi_counter < 10) {
    display.setCursor(100, 2);
  }
  else if (save_data.wakasagi_counter < 100) {
    display.setCursor(76, 2);
  }
  else if (save_data.wakasagi_counter < 1000) {
    display.setCursor(52, 2);
  }
  else if (save_data.wakasagi_counter < 10000) {
    display.setCursor(28, 2);
  }
  else {
    save_data.wakasagi_counter = 9999;
    display.setCursor(28, 2);
  }
  display.println(save_data.wakasagi_counter);
}

void wksg_DisplayDrawMotorSpeed() {
  display.setTextSize(1);
  display.setCursor(4, 39);
  display.println("Motor Speed");
  for(int i = 0; i < save_data.motor_speed; i++) {
    // 設定値を表示
    display.fillRect(4 + i * 24 + 2, 49, 20, 10, 1);
    if (motor_status) {
      // モーターが回転している場合の追加表示
      display.fillRect(4 + i * 24 + 2, 62, 20, 2, 1);
    }
  }
}
