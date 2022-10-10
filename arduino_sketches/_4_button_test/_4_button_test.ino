/*
 * TEST CODE FOR PROTOTYPE BOARD 
 * 
 * 3/18/2017
 * Author: @theDevilsVoice 
 * 
 */
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define OLED_RESET 2
Adafruit_SSD1306 display(OLED_RESET);
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
#define BRIGHT    350     //max led intensity (1-500)
#define INHALE    1250    //Inhalation time in milliseconds.
#define PULSE     INHALE*1000/BRIGHT
#define REST      100    //Rest Between Inhalations.

bool inputComplete = false;
/*
 * #define D0 16
#define D1 5 // I2C Bus SCL (clock)
#define D2 4 // I2C Bus SDA (data)
#define D3 0
#define D4 2 // Same as "LED_BUILTIN", but inverted logic
#define D5 14 // SPI Bus SCK (clock)
#define D6 12 // SPI Bus MISO 
#define D7 13 // SPI Bus MOSI
#define D8 15 // SPI Bus SS (CS)
#define D9 3 // RX0 (Serial console)
#define D10 1 // TX0 (Serial console)
 */

// DO NOT USE D8 (it is always low due to internal resistor)
 
int switchPin1 = D3;              // switch is connected to pin D3
int switchPin2 = D4;
int switchPin3 = D7;
int switchPin4 = D10;

// using the serial console pins as GPIO (DONT set Serial.begin())
//#define RX_PIN 3   // GPIO3
//#define TX_PIN 1   // GPIO1

void setup() {
  //Serial.begin(115200);
  delay(10);

  setup_display();

  pinMode(switchPin1, INPUT_PULLUP);    // Set the switch pin as input
  digitalWrite(switchPin1, HIGH); // turn on pull up resistor
  pinMode(switchPin2, INPUT_PULLUP);
  digitalWrite(switchPin2, HIGH);
  pinMode(switchPin3, INPUT_PULLUP);
  digitalWrite(switchPin3, HIGH);
  pinMode(switchPin4, INPUT_PULLUP);
  digitalWrite(switchPin4, HIGH);
  pinMode(LED_BUILTIN, OUTPUT); // initialize the on-board LED
  //digitalWrite(LED_BUILTIN, HIGH);  // turn LED off
}

void loop() {

  int status;
  display.setCursor(0, 0);
  //display.println("button test");
  display.display();
  showState();

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
    //Serial.println("Nothing just happened");
    //break;
  }
}

void showState() {
    if (digitalRead(switchPin1) == LOW) {               // check if the button is pressed
    //button_press("1");
    display.setCursor(0, 0);
    display.println("switch one LOW");
    display.display();
  } 
  if (digitalRead(switchPin1) == HIGH) {
    //button_press("2"); 
    display.setCursor(0, 0);
    display.println("switch one HIGH");
    display.display();
  }
  if (digitalRead(switchPin2) == LOW) {
    //button_press("3");
    display.setCursor(0, 8);
    display.println("switch two LOW");
    display.display();
  } 
  if (digitalRead(switchPin2) == HIGH) {
    //button_press("4");
    display.setCursor(0, 8);
    display.println("switch two HIGH");
    display.display();
  } 
  if (digitalRead(switchPin3) == LOW) {               // check if the button is pressed
    //button_press("1");
    display.setCursor(0, 16);
    display.println("switch three LOW");
    display.display();
  } 
  if (digitalRead(switchPin3) == HIGH) {
    //button_press("2"); 
    display.setCursor(0, 16);
     display.println("switch three HIGH");
    display.display();
  }
  if (digitalRead(switchPin4) == LOW) {
    //button_press("3");
    display.setCursor(0, 24);
    display.println("switch four LOW");
    display.display();
  } 
  if (digitalRead(switchPin4) == HIGH) {
    //button_press("4");
    display.setCursor(0, 24);
    display.println("switch four HIGH");
    display.display();
  } 
}
void button_press(String button_num) {
  //digitalWrite(LED_BUILTIN, LOW);   // turn LED on
  String msg = "Button " + button_num + " pressed";
  //Serial.println(msg);
  display.setCursor(0, 32);
  display.println(msg);
  display.display();
  led_half_breath();
  delay(100);
  //digitalWrite(LED_BUILTIN, HIGH);  // turn LED off
  digitalWrite(switchPin1, HIGH);
  digitalWrite(switchPin2, HIGH);
  digitalWrite(switchPin3, HIGH);
  digitalWrite(switchPin4, HIGH);
  //delay(200);
  display.setCursor(0, 0);
  display.clearDisplay();
  display.display();

}
/*
   by default, we'll generate the high voltage from the 3.3v line
   internally! (neat!)
   initialize with the I2C addr 0x3C (for the 128x32)
*/
void setup_display() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 4);
  display.clearDisplay();
  display.display();
}

void led_breath(){
     //ramp increasing intensity, Inhalation: 
  for (int i=1;i<BRIGHT;i++){
    digitalWrite(LED_BUILTIN, LOW);          // turn the LED on.
    delayMicroseconds(i*10);         // wait
    digitalWrite(LED_BUILTIN, HIGH);         // turn the LED off.
    delayMicroseconds(PULSE-i*10);   // wait
    delay(0);                        //to prevent watchdog firing.
  }
}

void led_half_breath() {
  
  //ramp decreasing intensity, Exhalation (half time):
  for (int i=BRIGHT-1;i>0;i--){
    digitalWrite(LED_BUILTIN, LOW);          // turn the LED on.
    delayMicroseconds(i*10);          // wait
    digitalWrite(LED_BUILTIN, HIGH);         // turn the LED off.
    delayMicroseconds(PULSE-i*10);  // wait
    i--;
    delay(0);                        //to prevent watchdog firing.
  }
  delay(REST);                       //take a rest...
}

