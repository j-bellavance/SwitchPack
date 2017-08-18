/*
 * Encoder.ino
 * Author: Jacques Bellavance
 * Date : August 13, 2017
 * Released under the GNU General Public License v3.0
 * 
 * Demonstrates how to use the Encoder class
 * Read a 4 steps per click encoder
 * .getRotation() returns 1 = CW, -1 = CCW
 * 
 * Control the brightness of two LEDs
 * Turning the encoder CCW decreases the brightness
 * Turning the encoder CW increases the brightness
 * Pressing the button changes the LED that is being adjusted.
 * 
 * Connections: PULLUP
 * [Encoder pin A]---D7
 * [Encoder pin C]---Ground
 * [Encoder pin B]---D8
 * 
*/

#include "SwitchPack.h"
Encoder anEncoder(7, 8);          //An encoder on pins 7 and 8
ModeSwitch mode(9, 2);            //A mode switch on pin 9, with two modes

byte pins[2] = {10, 11};          //Left an Right LEDs pins
byte brightness[2] = {85, 85};    //Left and Right Brightness
byte currentMode = 0;             //Current LED is Left

//setup==========================================================
void setup() {
  anEncoder.begin();                      //Setup the encoder
  mode.begin();                           //Setup the switch
  pinMode(pins[0], OUTPUT);               //Left LED
  pinMode(pins[1], OUTPUT);               //Right LED
  analogWrite(pins[0], brightness[0]);    //Left LED ON
  analogWrite(pins[1], brightness[1]);    //Right LED ON
}

//loop=================================================================================================
void loop(){
  int rotation;
  currentMode = mode.readMode();                                 //Read the switches' mode
  rotation = anEncoder.getRotation();                            //Read the encoder
  if (rotation != 0) {                                           //If turned
    brightness[currentMode] += (rotation << 2);                    //Increase or decrease brightness
    analogWrite(pins[currentMode], brightness[currentMode]);       //Adjust LED accordingly
  }
}


