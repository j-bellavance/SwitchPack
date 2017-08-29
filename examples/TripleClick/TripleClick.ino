/*
 * TripleClick.ino
 * Author: Jacques Bellavance
 * Date : August 9, 2017
 * Released under the GNU General Public License v3.0
 * 
 * Demonstrates how to use the DoubleClick class
 * The .clickCount() method returns the number of times that
 * the switch has been clicked during a specified period
 * 0 = no click
 * 1 = 1 click
 * 2 = 2 clicks
 * 3 = 3 clicks 
 * 
 * We will click the switch during half a second
 * After that, we will blink the debug LED (pin 13) 
 * the number of times that we clicked the switch
 * 
 * We use the DoubleClick class, but we use the
 * changeMaxClicks() method to make it a triple click
 * 
 * Connections: PULLUP
 * Ground---[Switch]---D2
 * 
 * Connections: PULLDOWN
 * +5V---[Switch]---|---[10Kohm Resistor]---Ground
 *                  |-----------------------D6 
*/

#define KEY_PIN 4
#define LED_PIN 13
#define BLINK_TIME 300
#define REACTION_TIME 500

#include "SwitchPack.h"
DoubleClick key(KEY_PIN, PULLUP, REACTION_TIME);

//blink=========================================
//Blink the debug LED (pin 13) "count" times
//If count = 0, the for loop will not be done
//----------------------------------------------
void blink(byte count) {
  for (int i = 1 ; i <= count; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(BLINK_TIME);
    digitalWrite(LED_PIN, LOW);
    delay(BLINK_TIME);
  }  
}//blink----------------------------------------

//setup==========
void setup() {
  key.begin();
  key.setMaxClicks(3);
  pinMode(LED_PIN, OUTPUT);
}

//loop=======================
void loop(){
  blink(key.clickCount());
}
