/*
 * ArrayOfClicks.ino
 * Author: Jacques Bellavance
 * Date : August 9, 2017
 * Released under the GNU General Public License v3.0
 * 
 * Demonstrates how to initialise and use an array of Click switches
 * Any other switch in the SwitchPack can be used this way
 * 
 * The setup uses 4 switches.
 * Switch 1 will blink LED 13 1 time, Switch 2 will blink LED 13 2 times, etc.
*/

#include "SwitchPack.h"
Click MYkeypad[] = {Click(2, PULLUP), Click(3, PULLUP), Click(4, PULLUP), Click(5, PULLUP)};

//readKeypad===================================
//Shows how to use a for( ; ; ) construct
//to read all the Click switches
//---------------------------------------------
byte readKeypad() {
  for (int i = 0 ; i < 4 ; i++) {
    if (MYkeypad[i].clicked()) return i + 1;
  }
  return 0;
}//readKeypad----------------------------------

//blink========================================
//Blink the debug LED (pin 13) "count" times
//---------------------------------------------
void blink(byte count) {
  for (int i = 1 ; i <= count; i++) {
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
    delay(500);
  }
}//blink---------------------------------------

//setup===============================================
void setup() {
  for (int i = 0 ; i < 4 ; i++) MYkeypad[0].begin();
}

//loop=======================================
void loop(){
   byte key = readKeypad();
   if (key > 0) blink(key);
}
