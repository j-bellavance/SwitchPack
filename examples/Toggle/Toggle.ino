/*
 * Toggle.ino
 * Author: Jacques Bellavance
 * Date : August 27, 2017
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
 * Ground---[Switch]---D4
 * 
*/

#define TOGGLE_PIN 4
#define LED_PIN 13

#include "SwitchPack.h"
Toggle toggle(TOGGLE_PIN, PULLUP);

//setup===================================================
void setup() {
  toggle.begin();
  toggle.setStatus(false); //off when the sketch begins
}

//loop==========================================
void loop(){
  digitalWrite(LED_PIN, toggle.readStatus());
}
