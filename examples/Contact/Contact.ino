/*
 * Contact.ino
 * Author: Jacques Bellavance
 * Date : August 9, 2017
 * Released under the GNU General Public License v3.0
 * 
 * Demonstrates how to use the Contact class
 * The .closed() method returns true if the switch's contact
 * is presently closed (conducting current).
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
Contact switch2(2, PULLUP);
Contact switch6(6, PULLDOWN);

//setup=======================
void setup() {
  switch2.begin();
  switch6.begin();
  pinMode(13, OUTPUT);
}

//loop===========================================
//Notice that now, there is no need to worry
//about pullup or pulldown mode being reverse.
//-----------------------------------------------
void loop(){
  if (switch2.closed()) digitalWrite(13, HIGH);
  else                  digitalWrite(13, LOW);
  if (switch6.closed()) digitalWrite(13, HIGH);
  else                  digitalWrite(13, LOW);
}
