/*
 * Encoder.ino
 * Author: Jacques Bellavance
 * Date : August 13, 2017
 * Released under the GNU General Public License v3.0
 * 
 * Demonstrates how to use the Encoder class
 * Read a 4 steps per click encoder
 * .getRotation() 
 *   returns CW (1) or CCW (-1)
 *   or 0 if not turned
 * 
 * Connections: PULLUP
 * [Encoder pin A]---D7
 * [Encoder pin C]---Ground
 * [Encoder pin B]---D8
 * 
*/

#include "SwitchPack.h"
Encoder anEncoder(7, 8);

//setup=========================
void setup() {
  Serial.begin(9600);
  anEncoder.begin();
}

//loop=================================
void loop(){
  int rotation;
  rotation = anEncoder.getRotation();
  if (rotation != 0) { 
    Serial.println(rotation);
  }
}


