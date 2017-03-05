/***************************************************
 
 _                _      _                   _           
| |__   __ _  ___| | __ | |__   __ _ _ __ __| | ___ _ __ 
| '_ \ / _` |/ __| |/ / | '_ \ / _` | '__/ _` |/ _ \ '__|
| | | | (_| | (__|   <  | | | | (_| | | | (_| |  __/ |   
|_| |_|\__,_|\___|_|\_\ |_| |_|\__,_|_|  \__,_|\___|_|   
                                                         
  
  
  Adafruit MQTT Library ESP8266 Example

  Must use ESP8266 Arduino from:
    https://github.com/esp8266/Arduino

  Works great with Adafruit's Huzzah ESP board & Feather
  ----> https://www.adafruit.com/product/2471
  ----> https://www.adafruit.com/products/2821

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Tony DiCola for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x32 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
// These next 4 are to drive the OLED
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


/*************************
  Adafruit.io Setup ******
**************************/
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  8883                   // use 8883 for SSL
#define AIO_USERNAME    ""
#define AIO_KEY         ""

#define OLED_RESET 2
Adafruit_SSD1306 display(OLED_RESET);

/********************** Global Variables Setup *******************************/
char handle[ ] = "p0lr";
char input[ ] = "";
bool inputComplete = false;
int BUTTON_PIN = D2; //button is connected to GPIO pin D1
const char* ssid = "";
const char* password = "";
//const char* mqtt_server = "broker.mqttdashboard.com";
//const char* mqtt_server = "iot.eclipse.org";
//const char* mqtt_server = "io.adafruit.com"

/************ Global State (you don't need to change this!) ******************/
// Create an ESP8266 WiFiClient class to connect to the MQTT server.
// WiFiClient client;
// or... use WiFiFlientSecure for SSL
WiFiClientSecure client;
// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/
Adafruit_MQTT_Publish toServer = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/toServer");
Adafruit_MQTT_Subscribe toBadge = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/toBadge");

/*************************** Sketch Code ************************************/
// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif


void setup() {
  Serial.begin(115200);
  delay(10);
  setup_display();
  setup_wifi();
  pinMode(BUTTON_PIN,INPUT);
  pinMode(LED_BUILTIN, OUTPUT); // initialize the on-board LED
  
  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&toBadge);
}

void loop() {
  int status;
  
  MQTT_connect();
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &toBadge) {
      //Serial.println((char *)toBadge.lastread);
    }
  }

  // Check for any button press
  // we will use this to simulate sensor data
  status=digitalRead(BUTTON_PIN);
  String msg="Button pressed";
  if(status==LOW )
  {
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on
    Serial.println(msg);
    display.println(msg);
    display.display();
  } 
  
  //Check to see if there is any serial data inbound
  if (Serial.available() > 0) {
  // read the incoming byte:
    char inChar[ ] = "";
    inChar[0] = (char)Serial.read();
    strcat(input, inChar);
    if (inChar[0] == '\n') {
      inputComplete = true;
    }
  }

  // Now we can publish stuff!
  if (inputComplete) {
    digitalWrite(LED_BUILTIN, HIGH);
    char post[ ] = "";
    strcat(post, handle);
    strcat(post, ": ");
    strcat(post, "Hello, World!");
    Serial.println(post);
    if (! toServer.publish(post)) {
      Serial.println(F("Failed"));
    } else {
//      input = " ";
      inputComplete = false;
    }
  }
  // ping the server to keep the mqtt connection alive
  // NOT required if you are publishing once every KEEPALIVE seconds
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }
}

void setup_display() {
  // by default, we'll generate the high voltage from the 3.3v line 
  // internally! (neat!)
  // initialize with the I2C addr 0x3C (for the 128x32)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);  
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

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  String msg="Connecting to MQTT... ";
  Serial.println(msg);
  display.println(msg);
  display.display();
  
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  msg = "MQTT Connected!";
  Serial.println(msg);
  display.println(msg);
  display.display();
  
}
