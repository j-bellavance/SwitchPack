/*
 * Contact.ino
 * Author: Jacques Bellavance
 * Date : August 27, 2017
 * Released under the GNU General Public License v3.0
 * 
 * Demonstrates how to use the Contact class
 * The .closed() method returns true if 
 * the switch's contact is presently closed.
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
Contact pullupSwitch(PULLUP_PIN, PULLUP);
Contact pulldownSwitch(PULLDOWN_PIN, PULLDOWN);

//setup=========================================================================
void setup() {
  pullupSwitch.begin();       //Instead of pinMode(PULLUP_PIN, INPUT_PULLUP);
  pulldownSwitch.begin();     //Instead of pinMode(PULLDOWN_PIN, INPUT);
  pinMode(13, OUTPUT);
}

//loop========================================================
//Notice that now, there is no need to worry
//about pullup or pulldown mode being reverse.
//------------------------------------------------------------
void loop(){
  if (pullupSwitch.closed()) digitalWrite(LED_PIN, HIGH);
  else                       digitalWrite(LED_PIN, LOW);
  if (pulldownSwitch.closed()) digitalWrite(LED_PIN, HIGH);
  else                         digitalWrite(LED_PIN, LOW);
}


