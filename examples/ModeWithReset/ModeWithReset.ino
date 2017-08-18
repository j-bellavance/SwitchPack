/*
 * ModeWithReset.ino
 * Author: Jacques Bellavance
 * Date : August 9, 2017
 * Released under the GNU General Public License v3.0
 * 
 * Demonstrates how to use the Mode class
 * The .changeMode() method changes the switch to the next mode
 * The .getMode() method returns the current mode of the switch
 * 
 * The number of modes is set on instantiation.
 * Each press pf the switch will set it in the next mode.
 * Modes are numbered from 0 to number of modes - 1
 * When the switch is in it's last mode, 
 * the next click will bring it back to 0
 * 
 * Ex.: 4 modes switch => 0, 1, 2, 3, 0, 1...
 * 
 * The constructor can accept an extra parameter: resetAfter (in milliseconds)
 * If set, and the chronometer is passed resetAfter, the mode is reset to 0
 * 
 * We will display decimal numbers 0..3 in binary with 2 leds
 * If the switch is not clicked for 2 seconds, the leds will turn off
 * 
 * Connections: PULLUP
 * Ground---[Switch]---D2
 * 
 * D11---LED---R220---Ground
 * D12---LED---R220---Ground
*/

#include "SwitchPack.h"
ModeSwitch switch2(2, PULLUP, 4, 2000);

//showDigital=============================================================
//Display a decimal 0..3 number in binary with LEDs
//pin 11 = Most significant bit
//pin 12 = Least significant bit
//------------------------------------------------------------------------
void showDigital(byte decimal) {
  switch(decimal) {
    case 0: { digitalWrite(11,  LOW); digitalWrite(12,  LOW); break; }
    case 1: { digitalWrite(11,  LOW); digitalWrite(12, HIGH); break; }
    case 2: { digitalWrite(11, HIGH); digitalWrite(12,  LOW); break; }
    case 3: { digitalWrite(11, HIGH); digitalWrite(12, HIGH); break; }
  }
}//showDigital------------------------------------------------------------

//setup=============
void setup() {
  switch2.begin();
  pinMode(11, OUTPUT); digitalWrite(11, LOW);
  pinMode(12, OUTPUT); digitalWrite(12, LOW);
}

//loop==============================
void loop(){
  switch2.readMode();
  showDigital(switch2.getMode());
}
