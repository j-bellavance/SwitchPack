/*
 * Repeater.ino
 * Author: Jacques Bellavance
 * Date : August 9, 2017
 * Released under the GNU General Public License v3.0
 * 
 * Demonstrates how to use the Repeater class
 * The .repeatRequired() method returns true if it is time to repeat an action
 * 
 * The Repeater switch acts just like the keys on a computer keyboard.
 * When first pressed, the action is undertaken. (ex.: send an 'A' to the console)
 * If it is pressed long enough, the action is repeated periodically until the switch is released
 * 
 * switch2 will send the character A to the monitor.
 * switch3 will send a CR/LF
 * 
 * Connections: PULLUP
 * Ground---[Switch]---D2
 * Ground---[Switch]---D3
 * 
*/

#include "SwitchPack.h"
Repeater switch2(2, PULLUP, 500, 50);
Click switch3(3, PULLUP);

//setup=================
void setup() {
  Serial.begin(9600);
  switch2.begin();
  switch3.begin();
}

//loop==============================
void loop(){
  if(switch2.repeatRequired()) Serial.print('A');
  if(switch3.clicked()) Serial.println();
}
