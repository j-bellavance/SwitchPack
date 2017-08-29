/*
 * TimedClick.ino
 * Author: Jacques Bellavance
 * Date : August 27, 2017
 * Released under the GNU General Public License v3.0
 * 
 * Demonstrates how to use the TimedClick class
 * The .clickTime() method returns the time in milliseconds that the switch was closed
 * The .timeSinceLastClick() method returns the time since the switch was last re-opened
 * 
 * Clicking "timer" will print the time it was closed
 * Clicking "since" will print the time since switch2 was re-opened
 * 
 * Connections: PULLUP
 * Ground---[Switch]---D4
 * 
 * Connections: PULLDOWN
 * +5V---[Switch]---|---[10Kohm Resistor]---Ground
 *                  |-----------------------D6
 * 
*/

#define TIMER_PIN 4
#define SINCE_PIN 6

#include "SwitchPack.h"
TimedClick timer(TIMER_PIN, PULLUP);
Click since(SINCE_PIN, PULLDOWN);

//setup=================
void setup() {
  Serial.begin(9600);
  timer.begin();
  since.begin();
}

//loop==============================
void loop(){
  if (timer.clicked()) {
    Serial.print(F("Timer was pressed for ")); 
    Serial.print(timer.clickTime()); 
    Serial.println(F(" milliseconds"));
  }
  if (since.clicked()) {
    Serial.print(F("Timer was released ")); 
    Serial.print(timer.timeSinceLastClick()); 
    Serial.println(F(" milliseconds ago"));
  }
}
