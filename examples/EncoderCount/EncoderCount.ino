/*
 * Encoder.ino
 * Author: Jacques Bellavance
 * Date : August 27, 2017
 * Released under the GNU General Public License v3.0
 * 
 * Demonstrates how to use the Encoder class
 * Read a 4 steps per click encoder
 * .getCount()
 *   returns the current value of the internal counter
 * 
 * Connections: PULLUP
 * [Encoder pin A]---D7
 * [Encoder pin C]---Ground
 * [Encoder pin B]---D8
 * 
*/

#define PIN_A 7
#define PIN_B 8

#include "SwitchPack.h"
Encoder anEncoder(PIN_A, PIN_B);

//setup=========================
void setup() {
  Serial.begin(9600);
  anEncoder.begin();
}

//loop=================================
void loop(){
  int count;
  count = anEncoder.getCount();
  Serial.println(count);
}


