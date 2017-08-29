/*
 * SwitchCycle.ino
 * Author: Jacques Bellavance
 * Date : August 27, 2017
 * Released under the GNU General Public License v3.0
 * 
 * Demonstrates how to use the Contact class
 * The .update() method returns in which phase the switch is presently in:
 * The .getClosed() method returns true if the switch's contact is presently closed
 * The .getOpen() method returns true if the switch's contact is presently open
 * The .getRose() method returns true if .update() saw the signal rising
 * The .getFell() method returns true if .update() saw the signal falling
 * 
 *                                            
 * 5V                      R|---------CLOSED--------|F
 *                         O|                       |E
 *                         S|                       |L
 *                         E|                       |L
 * 0V  --------OPEN---------|                       |--------OPEN---------
 * 
 * When the switch is open, debug LED (pin13) is off
 * When rising, left LED (pin 10) flashes
 * When the switch is closed, debug LED (pin 13) is on
 * When falling, right LED (pin 11) flashes
 * 
 * Connections: PULLUP
 * Ground---[Switch]---D4
 * 
*/

#define KEY_PIN 4
#define ROSE_PIN 10
#define FELL_PIN 11
#define CLOSED_PIN 13
#define BLINK_TIME 10

#include "SwitchPack.h"
Contact key(KEY_PIN, PULLUP);

//setup=========================
void setup() {
  key.begin();
  pinMode(ROSE_PIN, OUTPUT);
  pinMode(FELL_PIN, OUTPUT);
  pinMode(CLOSED_PIN, OUTPUT);
}

//loop==================================================
void loop(){
  key.update();
  if (key.getOpen())   digitalWrite(CLOSED_PIN, LOW);
  if (key.getRose()) { 
    digitalWrite(ROSE_PIN, HIGH);
    delay(BLINK_TIME);
    digitalWrite(ROSE_PIN, LOW);
  }  
  if (key.getClosed()) digitalWrite(CLOSED_PIN, HIGH);
  if (key.getFell()) {
    digitalWrite(FELL_PIN, HIGH);
    delay(BLINK_TIME);
    digitalWrite(FELL_PIN, LOW);
  }  
}


