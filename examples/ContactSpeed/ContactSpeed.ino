/*
 * Contact.ino
 * Author: Jacques Bellavance
 * Date : August 9, 2017
 * Released under the GNU General Public License v3.0
 * 
 * Contact switches return the current status of the switch.
 * It does so for every iteration of loop().
 * To demonstrate this, we will place a counter to find out
 * how many times the switch was scanned while 
 * we were pressing the switch
 * 
 * Connections: PULLUP
 * Ground---[Switch]---D2
 * 
*/

#include "SwitchPack.h"
Contact switch2(2, PULLUP);

//setup=======================
void setup() {
  Serial.begin(9600);
  switch2.begin();
}

//loop=========================================================================================
void loop(){
  if (switch2.closed()) {             //Read the switch and if it is closed,
     int count = 1;                     //Set count to 1
     while (switch2.closed()) {         //While we read the switch and it remains closed,
      count++;                            //Increase count
     }
     Serial.println(count);           //print the number of times the switch was scaned
  }
}
