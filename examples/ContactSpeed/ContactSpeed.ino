/*
 * ContactSpeed.ino
 * Author: Jacques Bellavance
 * Date : August 27, 2017
 * Released under the GNU General Public License v3.0
 * 
 * Contact switches return the current status of the switch.
 * It does so for every iteration of loop().
 * To demonstrate this, we will place a counter to find out
 * how many times the switch was scanned while 
 * we were pressing the switch
 * 
 *      |---------------|
 *      |               |
 * -----|               |----------
 *      ^               ^
 *    Switch          Switch
 *    Closed        re-opened
 *    
 *    Signal          Signal
 *     rose            fell
 *
 * Connections: PULLUP
 * Ground---[Switch]---D4
 * 
*/

#define KEY_PIN 4

#include "SwitchPack.h"
Contact key(KEY_PIN, PULLUP);

//setup=======================
void setup() {
  Serial.begin(9600);
  key.begin();
}

//loop=========================================================================================
void loop(){
  long count = 1;
  while(!key.fell()) {           //While the key did not "fell" (closed and re-opened),
    count++;                       //Increase count
  }
  Serial.println(count);     //print the number of times the switch was scaned
}
