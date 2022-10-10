#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`
#include "ESP8266WiFi.h"
#define UP 1
#define ESC 3
#define ENTER 2
#define DOWN 0
SSD1306 display(0x3c, D2, D1);

void setup() {
  display.init();
  display.flipScreenVertically();
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  pinMode(UP, INPUT_PULLUP);
  pinMode(ESC, INPUT_PULLUP);
  pinMode(ENTER, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
}

void loop() {
  if(WiFi.status() == 3) {

  }
  else {
    WiFi.begin("badger", "!dongle!");
    while (WiFi.status() != 3) {
      display.clear();
      display.setTextAlignment(TEXT_ALIGN_LEFT);
      display.setFont(ArialMT_Plain_10);
      display.drawString(0, 0, "Connecting to WiFi");
      display.display();
    }
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 0, "WiFi Connected");
    display.drawString(0, 10, String(WiFi.localIP()[0]) + "." + String(WiFi.localIP()[1]) + "." + String(WiFi.localIP()[2]) + "." + String(WiFi.localIP()[3]));
    display.display();
  }
}
/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 by Daniel Eichhorn
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */
