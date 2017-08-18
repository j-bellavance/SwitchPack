/*
 * TimedClick.ino
 * Author: Jacques Bellavance
 * Date : August 9, 2017
 * Released under the GNU General Public License v3.0
 * 
 * Demonstrates how to use the TimedClick class
 * The .clickTime() method returns the time in milliseconds that the switch was closed
 * 
 * The .timeSinceLastClick() method returns the time since the switch was last re-opened
 * 
 * Clicking switch2 will print the time it was closed
 * Clicking switch6 will print the time since switch2 was re-opened
 * 
 * Connections: PULLUP
 * Ground---[Switch]---D2
 * 
 * Connections: PULLDOWN
 * +5V---[Switch]---|---[10Kohm Resistor]---Ground
 *                  |-----------------------D6
 * 
*/

#include "SwitchPack.h"
TimedClick switch2(2, PULLUP);
Click switch6(6, PULLDOWN);

//setup=================
void setup() {
  Serial.begin(9600);
  switch2.begin();
  switch6.begin();
}

//loop==============================
void loop(){
  if (switch2.clicked()) {
    Serial.print(F("Switch 2 was pressed for ")); Serial.print(switch2.clickTime()); Serial.println(F(" milliseconds"));
  }
  if (switch6.clicked()) {
    Serial.print(F("Switch 2 was released ")); Serial.print(switch2.timeSinceLastClick()); Serial.println(F(" milliseconds ago"));
  }
}
