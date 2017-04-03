#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`
#include "ESP8266WiFi.h"

#define UP 1
#define ESC 3
#define ENTER 2
#define DOWN 0

SSD1306  display(0x3c, D2, D1);

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

String GetWiFiStatus(int StatusCode) {
  String output;
  if (StatusCode == 255) {
    output = "No Shield";
  }
  else if (StatusCode == 0) {
    output = "Idle";
  }
  else if (StatusCode == 1) {
    output = "No SSID Available";
  }
  else if (StatusCode == 2) {
    output = "Scan Completed";
  }
  else if (StatusCode == 3) {
    output = "Connected";
  }
  else if (StatusCode == 4) {
    output = "Connect Failed";
  }
  else if (StatusCode == 5) {
    output = "Connection Lost";
  }
  else if (StatusCode == 6) {
    output = "Disconnected";
  }
  else {
    output = "Unknown State " + String(StatusCode);
  }
  return output;
}

bool WiFiScanned = false;
int WiFiIndex = 0;
int WiFiCount = 0;
bool DisplayUpdate = true;

void loop() {
  if(WiFi.status() != WL_CONNECTED) {
    if(!WiFiScanned)
    {
      display.clear();
      display.setTextAlignment(TEXT_ALIGN_LEFT);
      display.setFont(ArialMT_Plain_16);
      display.drawString(0, 0, "Scanning WiFi");
      display.display();

      WiFiCount = WiFi.scanNetworks();
    
      if (WiFiCount == 0) {
        display.clear();
        display.setTextAlignment(TEXT_ALIGN_LEFT);
        display.setFont(ArialMT_Plain_10);
        display.drawString(0, 0, "No Networks Found");
        display.display();
      } else {
        WiFiScanned = true;
        DisplayUpdate = true;
      }
    }
    else
    {
      if (digitalRead(UP) == LOW) {
        WiFiIndex--;
        DisplayUpdate = true;
        if (WiFiIndex < 0) {
          WiFiIndex = 0;
        }
      }
      if (digitalRead(ESC) == LOW) {
        WiFiScanned = false;
        WiFiIndex = 0;
        DisplayUpdate = true;
      }
      if (digitalRead(ENTER) == LOW) {

        WiFi.disconnect();
        char ssid[] = "";
        WiFi.SSID(WiFiIndex).toCharArray(ssid, (WiFi.SSID(WiFiIndex).length() +1));
        
        WiFi.begin(ssid);

        while ((WiFi.status() != 3) && (digitalRead(ESC) != LOW)) {
          display.clear();
          display.setTextAlignment(TEXT_ALIGN_LEFT);
          display.setFont(ArialMT_Plain_10);
          String line1 = "Connecting to " + String(ssid);
          display.drawString(0, 0, line1);
          display.drawString(0, 10, GetWiFiStatus(WiFi.status()));
          display.display();
          delay(500);
        }
        
        if (WiFi.status() == 3) {
          display.clear();
          display.setTextAlignment(TEXT_ALIGN_LEFT);
          display.setFont(ArialMT_Plain_10);
          String line1 = "Connected";
          String line2 = "IP Address: " + String(WiFi.localIP()[0]) + "." + String(WiFi.localIP()[1]) + "." + String(WiFi.localIP()[2]) + "." + String(WiFi.localIP()[3]);
          display.drawString(0, 0, line1);
          display.drawString(0, 10, line2);
          display.display();
          delay(500);
        }

        if (digitalRead(ESC) == LOW) {
          WiFiScanned = 0;
          WiFiIndex = 0;
          DisplayUpdate = true;
        }
        
      }
      if (digitalRead(DOWN) == LOW) {
        WiFiIndex++;
        DisplayUpdate = true;
        if (WiFiIndex > WiFiCount - 1) {
          WiFiIndex = WiFiCount -1;
        }
      }

      if (DisplayUpdate) {
        display.clear();
        display.setTextAlignment(TEXT_ALIGN_LEFT);
        display.setFont(ArialMT_Plain_10);
        String line1 = "Networks: " + String(WiFiCount);
        display.drawString(0, 0, line1);
        String line2 = String(WiFiIndex + 1) + ": " + WiFi.SSID(WiFiIndex);
        display.drawString(0, 10, line2);
        String line3 = "Channel: " + String(WiFi.channel(WiFiIndex));
        display.drawString(0, 20, line3);
        String line4 = "Strength: " + String(WiFi.RSSI(WiFiIndex));
        display.drawString(0, 30, line4);
        String line5;
        if (WiFi.encryptionType(WiFiIndex) == 2) {
         line5 = "Encryption: WPA PSK";
        } else if (WiFi.encryptionType(WiFiIndex) == 4) {
         line5 = "Encryption: WPA2 PSK";
        } else if (WiFi.encryptionType(WiFiIndex) == 5) {
         line5 = "Encryption: WEP";
        } else if (WiFi.encryptionType(WiFiIndex) == 7) {
         line5 = "Encryption: None";
        } else if (WiFi.encryptionType(WiFiIndex) == 8) {
         line5 = "Encryption: WPA/WPA2";
        } else {
         line5 = "Encryption: Unknown";
        }
        display.drawString(0, 40, line5);
        display.display();
        DisplayUpdate = false;
        delay(200);
      }
    }
  }
  else {
    delay(1);
    //This is a placeholder for what to do when connected to the WiFi
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
