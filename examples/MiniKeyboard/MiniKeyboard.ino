/*
 * MiniKeyboard.ino
 * Author: Jacques Bellavance
 * Date : August 9, 2017
 * Released under the GNU General Public License v3.0
 * 
 * We will use different switches (5 of them) to implement a mini keyboard.
 * Switches 3 to 5 will be Repeater switches that will send the characters 'a', 'b' or 'c'
 * They will be placed in the MYkeypad[] array
 * Switch 2 will be a Contact switch used as a "Shift" key
 * Switch 6 will be a Toggle used as a "Lock upperCase" key
 * The debug LED (pin 13) will be used to show if the keyboard is in "Locked uppercase" mode
*/

#define NO_KEY 99
#define START 500
#define BURST 50
#define keyCount 3

#include "SwitchPack.h"
Repeater MYkeypad[] = {Repeater(3, PULLUP, START, BURST), Repeater(4, PULLUP, START, BURST), Repeater(5, PULLUP, START, BURST)};
Contact switch2(2, PULLUP);
Toggle switch6(6, PULLDOWN);

const char k[keyCount][2] = {'a', 'A', 
                             'b', 'B',
                             'c', 'C'};

//readKeypad======================================
//Shows how to use a for( ; ; ) construct
//to read all the Repeater switches
//------------------------------------------------
byte readKeypad() {
  for (int i = 0 ; i < keyCount ; i++) {
    if (MYkeypad[i].repeatRequired()) return i;
  }
  return NO_KEY;
}//readKeypad-------------------------------------

//setup===============================================
void setup() {
  Serial.begin(9600);
  for (int i = 0 ; i < 3 ; i++) MYkeypad[i].begin();
  switch2.begin();
  switch6.begin();
  pinMode(13, OUTPUT);
}

//loop===================================================
void loop(){
  bool uppercaseMode = switch6.readStatus();
  digitalWrite(13, uppercaseMode);
  byte key = readKeypad();
  if (key != NO_KEY) {
    bool upper = switch2.closed() || uppercaseMode;
    Serial.print(k[key][upper]);
  }
}










