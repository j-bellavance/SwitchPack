/*
* SwitchPack Library
* Author Jacques Bellavance
* Date : August 27, 2017
*
* Offers 9 classes to handle switches
* The hierarchy is as follows
*
*                                 [   Debounce   ]
*                                         |
*                                         |
*                                 [   Contact    ]
*                     ____________________|....................
*                     |                   |                   :
*             [   Repeater   ]    [     Click    ]    [    Encoder   ]
*            _____________________________|_______________________________
*            |                   |                   |                   |
*    [    Toggle    ]    [ DoubleClick  ]    [  ModeSwitch  ]    [  TimedClick  ]
*
*/

#include <Arduino.h>
#include "SwitchPack.h"

//===========================================================================================================Debounce
//Debounce===============
Debounce::Debounce(){} 

//debounce=====================================================================================
//pin: the pin that has to be debounced
//ABSTRACT
//  Do
//    Read pin n times (between 1 and 32)
//  While (pin reads are not identical)
//See https://github.com/j-bellavance/EdgeDebounce for the complete tutorial.
//---------------------------------------------------------------------------------------------
byte Debounce::pin(byte pin) { return debounce(pin); } //Alias (See DebounceAnyPin)
//---------------------------------------------------------------------------------------------
byte Debounce::debounce(byte pin) {
  unsigned long pinState;
  do {
    pinState = 0xffffffff;
    for (byte i = 1; i <= MYsensitivity; i++) pinState = (pinState << 1) | digitalRead(pin);
  } while ((pinState != debounceDontCare) && (pinState != 0xffffffff));
  return byte(pinState & 0x00000001);
}//debounce------------------------------------------------------------------------------------

//setSensitivity====================================================
//Sets the number of times that the pin is probed per burst reads
//Thanks to Jiggy-Ninja for the expression
//------------------------------------------------------------------
void Debounce::setSensitivity(byte sensitivity) {
  if (sensitivity >= 1 && sensitivity <= 32) {
    MYsensitivity = sensitivity;
    debounceDontCare = ~((1UL<<sensitivity)-1);
  }
}//setSensitivity---------------------------------------------------

//getSensitivity=======================================================
//Returns the number of times that the pin is probed per burst reads
//---------------------------------------------------------------------
byte Debounce::getSensitivity(){
  return MYsensitivity;
}//getSensitivity------------------------------------------------------

//============================================================================================================Contact
//Contact===============================================================
//----------------------
Contact::Contact() {}
//-------------------------------------------
Contact::Contact(byte pin) { MYpin = pin; }
//----------------------------------------------------------------------
Contact::Contact(byte pin, byte mode) { MYpin = pin; MYmode = mode; }

//sets================================================
//-----------------------------------------------
void Contact::setPin(byte pin) { MYpin = pin; }
//----------------------------------------------------
void Contact::setMode(byte mode) { MYmode = mode; }

//begin================================================================================
void Contact::begin() {	pinMode(MYpin, MYmode == PULLDOWN ? INPUT : INPUT_PULLUP); }
//----------------------------------------------------------------------------------
void Contact::begin(byte pin, byte mode) { MYpin = pin;	MYmode = mode; begin(); }

//update===================================================================================
//ABOUT MYmode:
//  The goal is to have a consistent answer about a switches' status
//  whether the pin is wired with a pullup or a pulldown resistor.
//  Returning closed() means exactly that, either way:  the switch is ON.
//  Since the pullup setup returns the opposite of pulldown,
//  we just to have negate the result if in pullup mode
//------------------------------------------------------------------------------------------
void Contact::update() {
  byte newStatus = debounce(MYpin);
  if (MYmode == PULLUP) newStatus = !newStatus;
  if (MYstatus == OPEN && newStatus == CLOSED) MYrose = true;
  else                                         MYrose = false;
  if (MYstatus == CLOSED && newStatus == OPEN) MYfell = true;
  else                                         MYfell = false;
  MYstatus = newStatus;
}//update------------------------------------------------------------------------------------

 //updatingMethods=============================================
bool Contact::closed() { update(); return MYstatus; }
bool Contact::open() { update(); return !MYstatus; }
bool Contact::rose() { update(); return MYrose; }
bool Contact::fell() { update(); return MYfell; }

//statusMethods=====================================================
bool Contact::getClosed() const { return MYstatus; }
bool Contact::getOpen()   const { return !MYstatus; }
bool Contact::getRose() const { return MYrose; }
bool Contact::getFell() const { return MYfell; }

//==============================================================================================================Click
//Click========================
//-----------------------------
Click::Click(): Contact() {}
//-----------------------------------------
Click::Click(byte pin) : Contact(pin) {}
 //---------------------------------------------------------
Click::Click(byte pin, byte mode) : Contact(pin, mode) {}

//clicked==================================================
//Returns true if Closed().
//Waits for the contact to be re-opened before returning
//---------------------------------------------------------
bool Click::clicked() {
  if (fell()) return true;
  else        return false;
 }//clicked-------------------------------------------------

//=============================================================================================================Toggle
//Toggle=====================
Toggle::Toggle(): Click() {}
//---------------------------------------------------------
Toggle::Toggle(byte pin) : Click(pin) {}
//------------------------------------------------------------
Toggle::Toggle(byte pin, byte mode) : Click(pin, mode) {}

//readStatus==================================================================================
byte Toggle::readStatus() {
  if (clicked()) MYstatus = !MYstatus;  //Read switch and change status if it was clicked()
  return MYstatus;                      //Return status
}//readStatus---------------------------------------------------------------------------------

//get/set Status==================================================
byte Toggle::getStatus() { return MYstatus; }
void Toggle::setStatus(byte status) { MYstatus = status; }

//========================================================================================================DoubleClick
//DoubleClick=============================
DoubleClick::DoubleClick() : Click() {}
//---------------------------------------------------
DoubleClick::DoubleClick(byte pin) : Click(pin) {}
//--------------------------------------------------------------------
DoubleClick::DoubleClick(byte pin, byte mode) : Click(pin, mode) {}
//--------------------------------------------------------------------------------
DoubleClick::DoubleClick(byte pin, byte mode, int limit) : Click(pin, mode) { MYlimit = limit; }

//clickCount========================================================================================
//Returns the number of times the switch has been clicked within the time set by "limit"
//
//--------------------------------------------------------------------------------------------------
byte DoubleClick::clickCount() {
  int clicks = 0;                                //Initialise counter
  if (clicked()) {                               //If clicked
    clicks++;                                      //Increase counter
    MYchrono = millis();                           //Reset chronometer
    while(millis() - MYchrono < MYlimit) {         //For the duration of "limit"
      if (clicked()) clicks++;                       //If clicked, increase counter
    }
  }
  if (clicks > MYmaxClicks) return MYmaxClicks;  //Make sure we don't exceed the allowed maximum
  else                      return clicks;
}//clickCount----------------------------------------------------------------------------------------

//changeMaxClicks=============================================================
//Allows to change the maximum number of clicks (Defaults to 2)
//----------------------------------------------------------------------------
void DoubleClick::setMaxClicks(byte maxClicks) { MYmaxClicks = maxClicks; }
//setLimit==================================================
//Allows to change "limit" after instantiation
//----------------------------------------------------------
void DoubleClick::setLimit(int limit) { MYlimit = limit; }

//=========================================================================================================TimedClick
//TimedClick============================
TimedClick::TimedClick() : Click() {}
//---------------------------------------------------
TimedClick::TimedClick(byte pin) : Click(pin) {}
//--------------------------------------------------------------------
TimedClick::TimedClick(byte pin, byte mode) : Click(pin, mode) {}

//clickTime=======================================================================
//Returns the time between when the switch was closed and when it was re-opened.
//--------------------------------------------------------------------------------
bool TimedClick::clicked() {
	MYtimeLastRead = millis();
  update();
  if (getRose()) {       //read the switch and if just rose
    MYstartTime = millis();         //Mark start time
  }
	if (getFell()) {                   //If it just rose
    MYendTime = millis();           //Mark end time
    return true;                    //Just clicked
  }
  return false;
}//clickTime----------------------------------------------------------------------

unsigned long TimedClick::wasLastRead() {
	return MYtimeLastRead;
}

//clickTime==============================================
unsigned long TimedClick::clickTime() 
  { if (getFell()) return MYendTime - MYstartTime;
    else           return 0; }

//timeSinceLastClick=============================
unsigned long TimedClick::timeSinceLastClick()
  { return millis() - MYendTime; }

//===========================================================================================================Repeater
//Repeater============================
Repeater::Repeater() : Contact() {}
//-----------------------------------------------
Repeater::Repeater(byte pin) : Contact(pin) {}
//----------------------------------------------------------------
Repeater::Repeater(byte pin, byte mode) : Contact(pin, mode) {}
//-----------------------------------------------------------------
Repeater::Repeater(byte pin, int start, int burst) : Contact(pin) 
          { MYstart = start;	MYburst = burst; }
//-----------------------------------------------------------------------------------
Repeater::Repeater(byte pin, byte mode, int start, int burst) : Contact(pin, mode) 
          { MYstart = start;	MYburst = burst; }

//repeatRequired==============================================================================
//When read repeatedly, it will return true every time the action is to be made.
//--------------------------------------------------------------------------------------------
bool Repeater::repeatRequired() {
  update();
  if (getOpen()) return false;             //If open, just return "NOT Required"
  if (getRose()) {                         //If the switch was just closed
     MYchrono = millis() + MYstart;          //Set chronometer to when the bursts should start
     return true;                            //And return "Required"
  }
  if (millis() >= MYchrono) {             //If time is up
    MYchrono = millis() + MYburst;          //Reset chronometer for next burst
    return true;                            //And return "Required"
  }
  return false;
}//repeatRequired------------------------------------------------------------------------------

//sets====================================================
void Repeater::setStart(int start) { MYstart = start; }
void Repeater::setBurst(int burst) { MYburst = burst; }

//=========================================================================================================ModeSwitch
//ModeSwitch============================
ModeSwitch::ModeSwitch() : Click() {}
//---------------------------------------------------------------------------------------
ModeSwitch::ModeSwitch(byte pin, int numModes) : Click(pin) {	MYnumModes = numModes; }
//--------------------------------------------------------------------------------------------------------
ModeSwitch::ModeSwitch(byte pin, byte mode, int numModes) : Click(pin, mode) { MYnumModes = numModes; }
//-----------------------------------------------------------------------------------------------
ModeSwitch::ModeSwitch(byte pin, byte mode, int numModes, int resetAfter) : Click(pin, mode) {
            MYnumModes = numModes;  MYresetAfter = resetAfter;  MYresetAllowed = true; }

//readMode===================================================================================
//Reset mode if allowed to and time expired
//Change mode if clicked
//-------------------------------------------------------------------------------------------
byte ModeSwitch::readMode() {
  if (MYresetAllowed && millis() > MYchrono + MYresetAfter) {  //If allowed and time is up
    MYcurrentMode = 0;                                           //Reset mode
    MYchrono = millis();                                         //Reset chronometer
  }
  if (clicked()) {                                             //If the switch was clicked
    MYcurrentMode = (MYcurrentMode + 1) % MYnumModes;            //Go to next mode
    MYchrono = millis();                                         //Reset chronometer
    return MYcurrentMode;                                        //return new mode
  }
  return MYcurrentMode;                                        //If not, return current mode
}//readMode------------------------------------------------------------------------------------

 //getMode===================================================================================
 //Reset mode if allowed to and time expired
 //Returns the current mode
 //------------------------------------------------------------------------------------------
byte ModeSwitch::getMode() {
	if (MYresetAllowed && millis() > MYchrono + MYresetAfter) {  //If allowed and time is up
		MYcurrentMode = 0;                                           //Reset mode
	}
	return MYcurrentMode;                                        //Return current mode
}//getMode-----------------------------------------------------------------------------------

//resetAfter====================================================================================
void ModeSwitch::resetAfter(int someTime) { MYresetAfter = someTime; MYresetAllowed = true; }

//============================================================================================================Encoder
//Encoder====================================================
Encoder::Encoder() { MYpinA.setPin(2); MYpinB.setPin(3); }
//-------------------------------------------------------------------------------------
Encoder::Encoder(byte pinA, byte pinB) { MYpinA.setPin(pinA);	MYpinB.setPin(pinB); }

//sets=============================================================================================
void Encoder::setPins(byte pinA, byte pinB) {	MYpinA.setPin(pinA); MYpinB.setPin(pinB); }
void Encoder::setModes(byte modeA, byte modeB) { MYpinA.setMode(modeA);	MYpinB.setMode(modeB); }

//begin=====================================================
void Encoder::begin() {	MYpinA.begin(); MYpinB.begin(); }

//stepsPerClick========================================================================
//Encoders defaults to 4 steps per click (the most common)
//Use this to match the encoder used Can be 2 or 4
void Encoder::stepsPerClick(byte stepsPerClick) { MYstepsPerClick = stepsPerClick; }

//rotation======================================================================
//Returns 1: CW or -1: CCW
//For 4 steps per click, the encoder is only probed for the rising edge of A
//For 2 steps per click, the encoder is also probed for the falling edge of A
//process: changes {0, 1} to {-1, 1} and updates count
//------------------------------------------------------------------------------
int Encoder::process(byte status) {	
  int temp = (status << 1) -1;  count += temp;  return temp; 
}//rotation---------------------------------------------------------------------
int Encoder::rotation() {
  MYpinA.update();
	int pinB = MYpinB.closed();
	if (MYpinA.getRose()) return process(pinB);
	if (MYstepsPerClick == 2 && MYpinA.getFell()) return process(!pinB);
  return 0;
}//rotation---------------------------------------------------------------------

//getRotation=========================================
int Encoder::getRotation() { return (rotation()); }

//count managers==================================================
int Encoder::getCount() { int foo = rotation(); return count; }
void Encoder::setCount(int value) { count = value; }
void Encoder::resetCount() {	count = 0; }
//count managers--------------------------------------------------

