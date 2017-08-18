/*
 * DoubleClick.ino
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
 * 
 * We will click the switch during half a second
 * After that, we will blink the debug LED (pin 13) 
 * the number of times that we clicked the switch
 * 
 * Connections: PULLUP
 * Ground---[Switch]---D2
 * 
 * Connections: PULLDOWN
 * +5V---[Switch]---|---[10Kohm Resistor]---Ground
 *                  |-----------------------D6 
*/

#include "SwitchPack.h"
DoubleClick switch2(2, PULLUP, 500);
DoubleClick switch6(6, PULLDOWN, 500);

//blink=======================================
//Blink the debug LED (pin 13)
//for 500 milliseconds as many times as count
//--------------------------------------------
void blink(byte count) {
  for (int i = 1 ; i <= count; i++) {
    digitalWrite(13, HIGH);
    delay(300);
    digitalWrite(13, LOW);
    delay(300);
  }  
}//blink--------------------------------------

//setup=============
void setup() {
  switch2.begin();
  switch6.begin();
}

//loop===========================
void loop(){
  blink(switch2.clickCount());
  blink(switch6.clickCount());
}
