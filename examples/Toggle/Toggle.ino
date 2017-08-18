/*
 * Toggle.ino
 * Author: Jacques Bellavance
 * Date : August 9, 2017
 * Released under the GNU General Public License v3.0
 * 
 * Demonstrates how to use the Toggle class
 * The .getStatus() method returns the status of the toggle
 * 0 = off
 * 1 = on
 * 
 * Use the .setStatus() method to initialise it
 * 
 * Connections: PULLUP
 * Ground---[Switch]---D2
 * 
*/

#include "SwitchPack.h"
Toggle switch2(2, PULLUP);

//setup================================================
void setup() {
  switch2.begin();
  switch2.setStatus(0); //off when the sketch begins
}

//loop====================================
void loop(){
  digitalWrite(13, switch2.readStatus());
}
