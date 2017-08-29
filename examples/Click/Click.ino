/*
 * Click.ino
 * Author: Jacques Bellavance
 * Date : August 27, 2017
 * Released under the GNU General Public License v3.0
 * 
 * Demonstrates how to use the Click class
 * The .clicked() method returns true if the switch's contact
 * is presently closed (conducting current).
 * It will wait for the switch to be re-opened before returning
 * 
 * Clicking the switch will blink the debug LED (pin 13) for half a second
 * Notice that the blink only happens when we release the switch.
 * 
 * Connections: PULLUP
 * Ground---[Switch]---D4
 * 
 * Connections: PULLDOWN
 * +5V---[Switch]---|---[10Kohm Resistor]---Ground
 *                  |-----------------------D6
 * 
*/

#define PULLUP_PIN 4
#define PULLDOWN_PIN 6
#define LED_PIN 13

#include "SwitchPack.h"
Click pullupSwitch(PULLUP_PIN, PULLUP);
Click pulldownSwitch(PULLDOWN_PIN, PULLDOWN);

//blink=========================
//Blink the debug LED (pin 13)
//for 500 milliseconds
//------------------------------
void blink() {
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
}//blink------------------------

//setup=====================
void setup() {
  pullupSwitch.begin();
  pulldownSwitch.begin();
}

//loop=====================================
void loop(){
  if (pullupSwitch.clicked()) blink();
  if (pulldownSwitch.clicked()) blink();
}
