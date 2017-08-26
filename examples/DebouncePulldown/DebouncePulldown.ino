/*
 * DebouncePulldown.ino
 * Author: Jacques Bellavance
 * Date : August 9, 2017
 * Released under the GNU General Public License v3.0
 * 
 * Demonstrates how to use the Debounce class to debounce a switch
 * Once the debouncer is created, it can debounce any digital pin
 * 
 * Connections:
 * +5V---[Switch]---|---[10Kohm Resistor]---Ground
 *                  |-----------------------D6
 */

#include "SwitchPack.h"
Debounce debounce;

//setup=======================
void setup() {
  pinMode(6, INPUT);
  pinMode(13, OUTPUT);
}

//loop=============================================
//In PULLDOWN mode, a normally open (NO) switch,
//which is the most common, behaves like this:
//when the switch is not pressed, it returns 0,
//when the switch is pressed, it returns 1.
//That is why we bring 13 HIGH when key is 1
//-------------------------------------------------
void loop(){
  byte key = debounce.pin(6);
  if (key == 1) digitalWrite(13, HIGH);
  else          digitalWrite(13, LOW);
}
