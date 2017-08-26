/*
 * DebouncePullup.ino
 * Author: Jacques Bellavance
 * Date : August 9, 2017
 * Released under the GNU General Public License v3.0
 * 
 * Demonstrates how to use the Debounce class to debounce a switch
 * Once the debouncer is created, it can debounce any digital pin
 * 
 * Connections:
 * Ground---[Switch]---D2
*/

#include "SwitchPack.h"
Debounce debounce;

//setup=======================
void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(13, OUTPUT);
}

//loop===========================================
//In PULLUP mode, a normally open (NO) switch,
//which is the most common, behaves like this:
//when the switch is not pressed, it returns 1,
//when the switch is pressed, it returns 0.
//That is why we bring 13 HIGH when key is 0
//-----------------------------------------------
void loop(){
  byte key = debounce.pin(2);
  if (key == 0) digitalWrite(13, HIGH);
  else          digitalWrite(13, LOW);
}
