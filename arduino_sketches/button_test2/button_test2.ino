/*
 *   
 
 _                _      _                   _           
| |__   __ _  ___| | __ | |__   __ _ _ __ __| | ___ _ __ 
| '_ \ / _` |/ __| |/ / | '_ \ / _` | '__/ _` |/ _ \ '__|
| | | | (_| | (__|   <  | | | | (_| | | | (_| |  __/ |   
|_| |_|\__,_|\___|_|\_\ |_| |_|\__,_|_|  \__,_|\___|_|   
                                                         
  
 *  Switch and Built-in LED test program
 *  
 *  @hackharder
 *  
 *  Save this file in a folder in your sketchbook
 *  For example:
 *  /home/thedevilsvoice/Arduino/sketchbook/button_test2
 *  
 *  On a single row: 
 *  Connect 10KΩ resistor between row and ground
 *  Connect jumper from pin D3 on esp-12e between resistor and switch
 *  Plug switch into opposite end of row from resistor
 *  
 *  Jumper other side of switch to power rail
 */
 

int switchPin = D3;              // switch is connected to pin D3
int val;                        // variable for reading the pin status


void setup() {
  //pinMode(ledPin, OUTPUT);      // Set the LED pin as output
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(switchPin, INPUT);    // Set the switch pin as input
  Serial.begin(115200);
}


void loop(){
  
  val = digitalRead(switchPin);   // read input value and store it in val
  if (val == HIGH) {               // check if the button is pressed
    digitalWrite(LED_BUILTIN, LOW);   // turn LED on
    String msg="Button pressed";
    Serial.println(msg);
    delay(1000);
    digitalWrite(LED_BUILTIN, HIGH);  // turn LED off
    delay(500);
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("Nothing just happened");
  }

}
