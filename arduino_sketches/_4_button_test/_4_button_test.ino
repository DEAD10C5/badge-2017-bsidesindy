#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
// These next 4 are to drive the OLED
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define AIO_SERVER      "6.6.6.1" 
#define AIO_SERVERPORT  8883                   // use 8883 for SSL
#define AIO_USERNAME    ""
#define AIO_KEY         ""

#define OLED_RESET 2
Adafruit_SSD1306 display(OLED_RESET);
#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

/********************** Global Variables Setup *******************************/
char handle[ ] = "p0lr";
char input[ ] = "";
bool inputComplete = false;
int switchPin1 = D9;              // switch is connected to pin D3
int switchPin2 = D0;
int switchPin3 = D4;
int switchPin4 = D3;
const char* ssid = "batpack";
const char* password = "batpack";
//const char* mqtt_server = "broker.mqttdashboard.com";
//const char* mqtt_server = "iot.eclipse.org";
//const char* mqtt_server = "io.adafruit.com"

void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);
  delay(10);
  setup_display();
  //setup_wifi();
  pinMode(switchPin1, INPUT);    // Set the switch pin as input
  digitalWrite(switchPin1, HIGH); // turn on pull up resistor
  pinMode(switchPin2, INPUT);
  digitalWrite(switchPin2, HIGH);
  pinMode(switchPin3, INPUT);
  digitalWrite(switchPin3, HIGH);
  pinMode(switchPin4, INPUT);
  digitalWrite(switchPin4, HIGH);
  pinMode(LED_BUILTIN, OUTPUT); // initialize the on-board LED
  digitalWrite(LED_BUILTIN, HIGH);  // turn LED off

}

void loop() {
  int status;


  if (digitalRead(switchPin1) == LOW) {               // check if the button is pressed
    button_press("1");
  } else if (digitalRead(switchPin2) == LOW) {
    button_press("2");
  } else if (digitalRead(switchPin3) == LOW) {
    button_press("3");
  } else if (digitalRead(switchPin4) == LOW) {
    button_press("4");
  }
  else {
    
    Serial.println("Nothing just happened");
  }
}

void button_press(String button_num) {
  digitalWrite(LED_BUILTIN, LOW);   // turn LED on
  String msg="Button " + button_num + " pressed";
  Serial.println(msg);
  display.println(msg);
  display.display();
  delay(300);
  digitalWrite(LED_BUILTIN, HIGH);  // turn LED off
  digitalWrite(switchPin1, HIGH);
  digitalWrite(switchPin2, HIGH);
  digitalWrite(switchPin3, HIGH);
  digitalWrite(switchPin4, HIGH);
  delay(200);
  display.clearDisplay();
  display.display();
    
}
void setup_display() {
  // by default, we'll generate the high voltage from the 3.3v line 
  // internally! (neat!)
  // initialize with the I2C addr 0x3C (for the 128x32)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);  
  display.clearDisplay();
  display.display();
}

void setup_wifi() {
  delay(100);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
      Serial.print(".");
    }
  randomSeed(micros());
  String msg="WiFi Connected!\nIP address: " + WiFi.localIP();
  Serial.println(msg);
  display.println(msg);
  display.display();
}

