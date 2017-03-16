#include "ESP8266WiFi.h"
#include <Wire.h>
#include <ACROBOTIC_SSD1306.h>

void setup()
{
  Wire.begin();	
  oled.init();                      // Initialze SSD1306 OLED display
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
}

void loop()
{
  int n = WiFi.scanNetworks();
  
  oled.clearDisplay();
  oled.setTextXY(0,0);
  oled.putString("Networks: ");
  oled.setTextXY(0,11);
  oled.putString(String(n));

  delay(5000);
}
