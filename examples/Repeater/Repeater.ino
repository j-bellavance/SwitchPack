/*
 * Repeater.ino
 * Author: Jacques Bellavance
 * Date : August 27, 2017
 * Released under the GNU General Public License v3.0
 * 
 * Demonstrates how to use the Repeater class
 * The .repeatRequired() method returns true if it is time to repeat an action
 * 
 * The Repeater switch acts just like the keys on a computer keyboard.
 * When first pressed, the action is undertaken. (ex.: send an 'A' to the console)
 * If it is pressed long enough, the action is repeated periodically until the switch is released
 * 
 * keyA will send the character A to the monitor.
 * crLf will send a CR/LF
 * 
 * Connections: PULLUP
 * Ground---[Switch]---D4
 * Ground---[Switch]---D5
 * 
*/

#define KEYA_PIN 4
#define CRLF_PIN 5

#include "SwitchPack.h"
Repeater keyA(KEYA_PIN, PULLUP, 500, 50);
Click crLf(CRLF_PIN, PULLUP);

//setup=================
void setup() {
  Serial.begin(9600);
  keyA.begin();
  crLf.begin();
}

//loop==============================
void loop(){
  if(keyA.repeatRequired()) Serial.print('A');
  if(crLf.clicked()) Serial.println();
}
