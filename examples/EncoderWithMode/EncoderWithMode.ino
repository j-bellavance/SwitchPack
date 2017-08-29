/*
 * EncoderWithMode.ino
 * Author: Jacques Bellavance
 * Date : August 27, 2017
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
 *          [Encoder pin A]-----D7
 * Ground---[Encoder pin C]
 *          [Encoder pin B]-----D8
 * Ground---[EncoderSwitch]-----D9
 * Ground---[LED1]---[220ohm]---D11
 * Ground---[LED2]---[220ohm]---D12
 * 
*/

#define PIN_A 7
#define PIN_B 8
#define SWITCH_PIN 9
#define NUM_MODES 2
#define LED0_PIN 10
#define LED1_PIN 11
#define PWM_START_AT 85

#include "SwitchPack.h"
Encoder anEncoder(PIN_A, PIN_B);          
ModeSwitch mode(SWITCH_PIN, NUM_MODES);

byte pins[2] = {LED0_PIN, LED1_PIN};                  //Left an Right LEDs pins
byte brightness[2] = {PWM_START_AT, PWM_START_AT};    //Left and Right Brightness
byte currentMode = 0;                                 //Current LED is Left

//setup==========================================================
void setup() {
  anEncoder.begin();                      //Setup the encoder
  mode.begin();                           //Setup the switch
  pinMode(pins[0], OUTPUT);               //Left LED
  pinMode(pins[1], OUTPUT);               //Right LED
  analogWrite(pins[0], brightness[0]);    //Bring left LED ON
  analogWrite(pins[1], brightness[1]);    //Bring right LED ON
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


