/*
 * ArrayOfClicks.ino
 * Author: Jacques Bellavance
 * Date : August 27, 2017
 * Released under the GNU General Public License v3.0
 * 
 * Demonstrates how to initialise and use an array of Click switches
 * Any other switch in the SwitchPack can be used this way
 * 
 * The setup uses 5 switches.
 * Switches on pins 2, 3, 4 and 5 are in pullup mude
 * Switch 6 is in pulldown mode
 * 
 * Switch 2 will blink LED 13 two times, 
 * Switch 3 will blink LED 13 three times, etc.
 * 
*/

#define LED_PIN 13
#define SWITCH_COUNT 5

#include "SwitchPack.h"
Click keypad[] = {Click(2, PULLUP), Click(3, PULLUP), 
                  Click(4, PULLUP), Click(5, PULLUP), 
                  Click(6, PULLDOWN)};

//readKeypad===================================
//Shows how to use a for( ; ; ) construct
//to read all the Click switches
//keypad[] is indexed 0..4
//We add 2 to get an index of 2..6
//If no switch was clicked, we return 0
//---------------------------------------------
byte readKeypad() {
  for (int i = 0 ; i < SWITCH_COUNT ; i++) {
    if (keypad[i].clicked()) return i + 2;
  }
  return 0;
}//readKeypad----------------------------------

//blink========================================
//Blink the debug LED (pin 13) "count" times
//---------------------------------------------
void blink(byte count) {
  for (int i = 1 ; i <= count; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(500);
    digitalWrite(LED_PIN, LOW);
    delay(500);
  }
}//blink---------------------------------------

//setup=========================================================
void setup() {
  for (int i = 0 ; i < SWITCH_COUNT ; i++) keypad[i].begin();
}

//loop========================
void loop(){
   byte key = readKeypad();
   if (key > 0) blink(key);
}
