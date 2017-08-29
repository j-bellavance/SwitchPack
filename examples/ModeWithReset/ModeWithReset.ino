/*
 * ModeWithReset.ino
 * Author: Jacques Bellavance
 * Date : August 27, 2017
 * Released under the GNU General Public License v3.0
 * 
 * Demonstrates how to use the Mode class with the timer reset chronometer
 * The .readMode() method returns the current mode of the switch
 * 
 * The number of modes is set on instantiation.
 * Each press of the switch will set it in the next mode.
 * Modes are numbered from 0 to number of modes - 1
 * When the switch is in it's last mode, 
 * the next click will bring it back to 0
 * 
 * Ex.: 4 modes switch => 0, 1, 2, 3, 0, 1...
 * 
 * The .resetAfter() method adds a chronometer to the class
 * If set, and the chronometer is passed resetAfter, the mode is reset to 0
 * Each time the mode switch is pressed, the chronometer is reset.
 * This method is used after the .begin() statement in the setup() section of the script
 * 
 * We will display decimal numbers 0..3 in binary with 2 leds
 * If the switch is not clicked for 2 seconds, the leds will turn off
 * 
 * Connections: PULLUP
 * Ground---[Switch]---D4
 * D10---LED---R220----Ground
 * D11---LED---R220----Ground
*/

#define MODE_PIN 4
#define LED0_PIN 10
#define LED1_PIN 11
#define NUM_MODES 4
#define RESET_AFTER 2000

#include "SwitchPack.h"
ModeSwitch mode(MODE_PIN, NUM_MODES);

//showDigital========================================================================
//Display a decimal 0..3 number in binary with LEDs
//LED0 = Most significant bit
//LED1 = Least significant bit
//-----------------------------------------------------------------------------------
void showDigital(byte decimal) {
  switch(decimal) {
    case 0: { digitalWrite(LED0_PIN,  LOW); digitalWrite(LED1_PIN,  LOW); break; }
    case 1: { digitalWrite(LED0_PIN,  LOW); digitalWrite(LED1_PIN, HIGH); break; }
    case 2: { digitalWrite(LED0_PIN, HIGH); digitalWrite(LED1_PIN,  LOW); break; }
    case 3: { digitalWrite(LED0_PIN, HIGH); digitalWrite(LED1_PIN, HIGH); break; }
  }
}//showDigital-----------------------------------------------------------------------

//setup=====================================================
void setup() {
  mode.begin();
  mode.resetAfter(RESET_AFTER);
  pinMode(LED0_PIN, OUTPUT); digitalWrite(LED0_PIN, LOW);
  pinMode(LED1_PIN, OUTPUT); digitalWrite(LED1_PIN, LOW);
}

//loop==============================
void loop(){
  showDigital(mode.readMode());
}
