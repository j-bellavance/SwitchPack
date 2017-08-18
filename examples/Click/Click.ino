/*
 * Click.ino
 * Author: Jacques Bellavance
 * Date : August 9, 2017
 * Released under the GNU General Public License v3.0
 * 
 * Demonstrates how to use the Click class
 * The .clicked() method returns true if the switch's contact
 * is presently closed (conducting current).
 * It will wait for the switch to be re-opened before returning
 * 
 * Clicking the switch will blink the debug LED (pin 13) for half a second
 * Notice that the blink only happen when we release the switch.
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
Click switch2(2, PULLUP);
Click switch6(6, PULLDOWN);

//blink=========================
//Blink the debug LED (pin 13)
//for 500 milliseconds
//------------------------------
void blink() {
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
}//blink------------------------

//setup=============
void setup() {
  switch2.begin();
  switch6.begin();
}

//loop==============================
void loop(){
  if (switch2.clicked()) blink();
  if (switch6.clicked()) blink();
}
