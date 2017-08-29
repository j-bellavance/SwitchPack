/*
 * MiniKeyboard.ino
 * Author: Jacques Bellavance
 * Date : August 27, 2017
 * Released under the GNU General Public License v3.0
 * 
 * We will use different switches (5 of them) to implement a mini keyboard.
 * Switches 3 to 5 will be Repeater switches that will send the characters 'a', 'b' or 'c'
 * They will be placed in the keypad[] array
 * Switch 2 will be a Contact switch used as a "Shift" key
 * Switch 6 will be a Toggle used as a "Lock upperCase" key
 * The debug LED (pin 13) will be used to show if the keyboard is in "Locked uppercase" mode
 * 
*/

#define NO_KEY 99
#define SHIFT_PIN 2
#define LOCK_PIN 6
#define START 500
#define BURST 50
#define KEY_COUNT 3
#define LED_PIN 13

#include <SwitchPack.h>
Repeater keypad[] = {Repeater(3, PULLUP, START, BURST), 
                     Repeater(4, PULLUP, START, BURST), 
                     Repeater(5, PULLUP, START, BURST)};
                       
Contact shift(SHIFT_PIN, PULLUP);
Toggle lock(LOCK_PIN, PULLDOWN);

//The line pointer selects the letter
//The column pointer selects upper/lower case
const char k[KEY_COUNT][2] = {'a', 'A', 
                              'b', 'B',
                              'c', 'C'};

//readKeypad====================================
//Shows how to use a for( ; ; ) construct
//to read all the Repeater switches
//Returns the key to print (0..2) if required
//Returns NO_KEY otherwise
//----------------------------------------------
byte readKeypad() {
  for (int i = 0 ; i < KEY_COUNT ; i++) {
    if (keypad[i].repeatRequired()) return i;
  }
  return NO_KEY;
}//readKeypad-----------------------------------

//setup==============================================
void setup() {
  Serial.begin(9600);
  for (int i = 0 ; i < 3 ; i++) keypad[i].begin();
  shift.begin();
  lock.begin();
  pinMode(LED_PIN, OUTPUT);
}

//loop==========================================================================================================================
void loop(){
  bool uppercaseMode = lock.readStatus();                  //Read lock status
  digitalWrite(LED_PIN, uppercaseMode);                    //Update lock status LED
  byte key = readKeypad();                                 //Read the keypad
  if (key != NO_KEY) {                                     //If a key is required (NOT NO_KEY)
    bool upper = shift.closed() || uppercaseMode;            //Current uppercase status = shift is closed OR in uppercaseMode
    Serial.print(k[key][upper]);                             //Send character to the serial monitor
  }
}










