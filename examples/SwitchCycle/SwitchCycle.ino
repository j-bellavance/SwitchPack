/*
 * SwitchCycle.ino
 * Author: Jacques Bellavance
 * Date : August 9, 2017
 * Released under the GNU General Public License v3.0
 * 
 * Demonstrates how to use the Contact class
 * The .closed() method returns true if the switch's contact is presently closed (conducting current).
 * The .open() method returns true if the switch's contact is presently open (not conducting current).
 * The .rose() method returns true if the last call to .closed() or to .open() was on the rise of the signal.
 * The .fell() method returns true if the last call to .closed() or to .open() was on the fall of the signal.
 * 
 *                                            
 * 5V                      R|---------CLOSED--------|F
 *                         I|                       |A
 *                         S|                       |L
 *                         E|                       |L
 * 0V  --------OPEN---------|                       |-----
 * 
 * When the switch is open, debug LED (pin13) is off
 * When rising, left LED (pin 11) flashes
 * When the switch is closed, debug LED (pin 13) is on
 * When falling, right LED (pin 12) flashes
 * 
 * 
 * Connections: PULLUP
 * Ground---[Switch]---D2
 * 
*/

#include "SwitchPack.h"
Contact switch2(2, PULLUP);

//setup=======================
void setup() {
  switch2.begin();
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
}

//loop==========================
void loop(){
  if (switch2.closed()) { 
    digitalWrite(13, HIGH); 
    if (switch2.rose()) { 
      digitalWrite(11, HIGH); 
      delay(5); 
      digitalWrite(11, LOW); 
    }
  }
  else {
    digitalWrite(13, LOW); 
    if (switch2.fell()) { 
      digitalWrite(12, HIGH); 
      delay(5
      ); 
      digitalWrite(12, LOW); 
    }
  }
}
