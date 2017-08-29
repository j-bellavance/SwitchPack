/*
 * DebounceAnyPin.ino
 * Author: Jacques Bellavance
 * Date : August 27, 2017
 * Released under the GNU General Public License v3.0
 * 
 * Demonstrates how to use the Debounce class to debounce a switch
 * There is a switch in pullup mode on pin 4
 * and a switch in pulldown mode on pin 6
 * Pressing either one will bring the Debug LED on pin 13 HIGH
 * Once the debouncer is instantiated, it can debounce any digital pin
 * 
 * Connections:
 * Ground---[Switch]-------------------D4
 * +5V------[Switch]---+---------------D6
 *                     +---[10K Ohm]---Ground
 *
*/

#define PULLUP_PIN 4
#define PULLDOWN_PIN 6
#define LED_PIN 13

#include "SwitchPack.h"
Debounce debounce;

//setup================================
void setup() {
  pinMode(PULLUP_PIN, INPUT_PULLUP);
  pinMode(PULLDOWN_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

//loop==============================================================
//In PULLUP mode, we bring the LED HIGH when the switch reads 0
//In PULLDOWN mode, we bring the LED HIGH when the switch reads 1
//------------------------------------------------------------------
void loop(){
  byte key;
  key = debounce.pin(PULLUP_PIN);
  if (key == 0) digitalWrite(LED_PIN, HIGH);
  else          digitalWrite(LED_PIN, LOW);

  key = debounce.pin(PULLDOWN_PIN);
  if (key == 1) digitalWrite(LED_PIN, HIGH);
  else          digitalWrite(LED_PIN, LOW);
}


