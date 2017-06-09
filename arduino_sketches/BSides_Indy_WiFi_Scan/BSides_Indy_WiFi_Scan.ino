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

String BadSSID[] = "";

String GetWiFiStatus(int StatusCode) {
  if (StatusCode == 255) {
    return("No Shield");
  } else if (StatusCode == 0) {
    return("Idle");
  } else if (StatusCode == 1) {
    return("SSID Unavailable");
  } else if (StatusCode == 2) {
    return("Scan Completed");
  } else if (StatusCode == 3) {
    return("Connected");
  } else if (StatusCode == 4) {
    return("Connect Failed");
  } else if (StatusCode == 5) {
    return("Connection Lost");
  } else if (StatusCode == 6) {
    return("Disconnected");
  } else {
    return("Unknown State " + String(StatusCode));
  }
}

String GetWiFiEncryption(int StatusCode) {
  if (StatusCode == 2) {
    return("WPA PSK");
  } else if (StatusCode == 4) {
    return("WPA2 PSK");
  } else if (StatusCode == 5) {
    return("WEP");
  } else if (StatusCode == 7) {
    return("None");
  } else if (StatusCode == 8) {
    return("WPA/WPA2");
  } else {
    return("Unknown");
  }
}

bool WiFiScanned = false;
int WiFiIndex = 0;
int WiFiCount = 0;
bool DisplayUpdate = true;

void loop() {
  if(WiFi.status() != 3) {
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
          display.drawString(0, 0, "Connecting to " + String(ssid));
          display.drawString(0, 10, GetWiFiStatus(WiFi.status()));
          display.display();
          delay(500);
        }
        
        if (WiFi.status() == 3) {
          display.clear();
          display.setTextAlignment(TEXT_ALIGN_LEFT);
          display.setFont(ArialMT_Plain_10);
          display.drawString(0, 0, "Connected");
          display.drawString(0, 10, "IP: " + String(WiFi.localIP()[0]) + "." + String(WiFi.localIP()[1]) + "." + String(WiFi.localIP()[2]) + "." + String(WiFi.localIP()[3]));
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
          WiFiIndex = WiFiCount - 1;
        }
      }

      if (DisplayUpdate) {
        display.clear();
        display.setTextAlignment(TEXT_ALIGN_LEFT);
        display.setFont(ArialMT_Plain_10);
        display.drawString(0, 0, "Networks: " + String(WiFiCount));
        display.drawString(0, 10, String(WiFiIndex + 1) + ": " + WiFi.SSID(WiFiIndex));
        display.drawString(0, 20, "Channel: " + String(WiFi.channel(WiFiIndex)));
        display.drawString(0, 30, "Strength: " + String(WiFi.RSSI(WiFiIndex)));
        display.drawString(0, 40, "Encryption: " + GetWiFiEncryption(WiFi.encryptionType(WiFiIndex)));
        display.display();
        DisplayUpdate = false;
        delay(200);
      }
    }
  }
  else {
    if (digitalRead(ESC) == LOW) {
      WiFi.disconnect();
      WiFiScanned = false;
      WiFiIndex = 0;
      DisplayUpdate = true;
    }  
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
