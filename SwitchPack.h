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



#ifndef SwitchPack_h
#define SwitchPack_h

#define OPEN 0
#define CLOSED 1
#define PULLUP 0
#define PULLDOWN 1
#define STABLE 0
#define FALLING 1
#define RISING 2
#define CW 1
#define CCW -1
#define ON 1
#define OFF 0

//============================================================================Debounce
//Same as EdgeDebounce
//See : https://github.com/j-bellavance/EdgeDebounce
//It was inspired by this article: http://www.ganssle.com/debouncing.htm
//-----------------------------------------------------
class Debounce {
  public:
    Debounce();
    virtual byte debounce(byte pin);
    virtual byte pin(byte pin);
    virtual void setSensitivity(byte sensitivity);
    virtual byte getSensitivity();
  protected:
    byte MYsensitivity = 16;
    unsigned long debounceDontCare = 0xffff0000;
};//Debounce-------------------------------------------

//=============================================================================Contact
//Constructor: (Inherits Debounce)
//  pin: the Arduino pin on which the switch attached
//  mode: either PULLUP or PULLDOWN depending on the wiring
//closed(): Returns true if the contact is closed
//begin(): Initialises the pin (INPUT_PULLUP or INPUT)
//------------------------------------------------------------
class Contact : public Debounce {
  public:
    Contact();
    Contact(byte pin);
    Contact(byte pin, byte mode);
    virtual void begin();
    virtual void begin(byte pin, byte mode);
    virtual void update();
    virtual bool closed();
    virtual bool open();
    virtual bool rose();
    virtual bool fell();
    virtual bool getClosed() const;
    virtual bool getOpen() const;
    virtual bool getRose() const;
    virtual bool getFell() const;
    virtual void setPin(byte pin);
    virtual void setMode(byte mode);
  protected:
    byte MYpin;
    byte MYmode = PULLUP;
    bool MYstatus = false;
    bool MYrose;
    bool MYfell;
    byte MYedge = STABLE;
  private:
    bool firstPass = true;
};//Contact---------------------------------------------------

//===============================================================================Click
//Constructor: (Inherits Contact)
//  pin: the Arduino pin on which the switch attached
//  mode: either PULLUP or PULLDOWN depending on the wiring
//clicked(): Returns true if the switch was closed.
//           Waits for the switch to be re-opened before returning
//-------------------------------------------------------------------
class Click : public Contact {
  public:
    Click();
    Click(byte pin);
    Click(byte pin, byte mode);
    virtual bool clicked();
};//Click------------------------------------------------------------

//==============================================================================Toggle
//Constructor: (Inherits Click)
//  pin: the Arduino pin on which the switch attached
//  mode: either PULLUP or PULLDOWN depending on the wiring
//getStatus():
//  If the switch is clicked, The toggle's status
//  changes from true to false and vice versa.
//setStatus():
//  status: true or false
//  Used to set the original status of the toggle.
//------------------------------------------------------------
class Toggle : public Click {
 
  public:
    Toggle();
    Toggle(byte pin);
    Toggle(byte pin, byte mode);
    virtual byte readStatus();
    virtual byte getStatus();
    virtual void setStatus(byte status);
  protected:
    bool MYstatus;
};//Toggle----------------------------------------------------

//=========================================================================DoubleClick
//Constructor: (Inherits Click)
//  pin: the Arduino pin on which the switch attached
//  mode: either PULLUP or PULLDOWN depending on the wiring
//  limit: the minimum time in milliseconds between
//         two clicks to be considered a double click.
//clickCount(): 
//  Returns 0 => Switch was not pressed
//  Returns 1 => Switch was pressed once within "limit"
//  Returns 2 => Switch was pressed twice within "limit"
//  NOTE: Pressing more than 2 times will be reported as 2
//setLimit():
//  Allows to change the "limit" after instantiation.
//  setMaxClicks():
//Allows to have TripleClick, QuadrupleClick, ...
//---------------------------------------------------------------
class DoubleClick : public Click {
  public:
    DoubleClick();
    DoubleClick(byte pin);
    DoubleClick(byte pin, byte mode);
    DoubleClick(byte pin, int limit);
    DoubleClick(byte pin, byte mode, int limit);
    virtual byte clickCount();
    virtual void setLimit(int limit);
    virtual void setMaxClicks(byte maxClicks);
  private:
    int MYlimit;
    byte MYmaxClicks = 2;
    unsigned long MYchrono;  
};//DoubleClick--------------------------------------------------

//==========================================================================TimedClick
//Constructor: (Inherits Contact)
//  pin: the Arduino pin on which the switch attached
//  mode: either PULLUP or PULLDOWN depending on the wiring
//clickTime(): 
//  Time in milliseconds that the switch was closed.
//timeSinceLastClick():
//  The time between now and when the switch was last re-opened
//----------------------------------------------------------------
class TimedClick : public Click {
  public:
    TimedClick();
    TimedClick(byte pin);
    TimedClick(byte pin, byte mode);
    virtual bool clicked();
    virtual unsigned long wasLastRead();
    virtual unsigned long clickTime();
    virtual unsigned long timeSinceLastClick();
  private:
    unsigned long MYtimeLastRead;
    unsigned long MYstartTime;
    unsigned long MYendTime;
};//TimedClik-----------------------------------------------------

//============================================================================Repeater
//Constructor: (Inherits Contact)
//  pin: the Arduino pin on which the switch attached
//  mode: either PULLUP or PULLDOWN depending on the wiring
//  start: the time in millseconds before action is repeated
//  burst: the time in milliseconds between subsequent actions
//NOTE:
//  Operates exactly as the keys on the keyboard.
//  The first action is taken immediately after the switch is closed
//  After "start" time, the action is repeated every "burst" period
//repeatRequired():
//  When read repeatedly, it will return true every time the action is to be made.
//setStart():
//  Allows to specify a new "start" time after instantiation
//setBurst():
//  Allows to specify a new "burst" time after instantiation
//---------------------------------------------------------------------------------
class Repeater : public Contact {
  public:
    Repeater();
    Repeater(byte pin);
    Repeater(byte pin, byte mode);
    Repeater(byte pin, int start, int burst);
    Repeater(byte pin, byte mode, int start, int burst);
    virtual bool repeatRequired();
    virtual void setStart(int start);
    virtual void setBurst(int burst);
  private:
    int MYstart;
    int MYburst;
    byte MYoldState;
    unsigned long MYchrono;
};//------------------------------------------------------------------

//==========================================================================ModeSwitch
//Constructor: (Inherits Click)
//  pin: the Arduino pin on which the switch attached
//  mode: either PULLUP or PULLDOWN depending on the wiring
//  numModes: the number of modes of the switch
//  resetAfter: the time in milliseconds after which the switch 
//              reverts to mode 0 (extended constructor)
//Each click increases the mode, up until the the switch is in it's
//last mode. The next click will revert to mode 0.
//Ex.: For a 4 mode switch, successive clicks will place
//     the switch in modes {0, 1, 2, 3, 0, 1, 2, 3, 0,...}
//--------------------------------------------------------------------
class ModeSwitch : public Click {
  public:
    ModeSwitch();
    ModeSwitch(byte pin, int numModes);
    ModeSwitch(byte pin, byte mode, int numModes);
    ModeSwitch(byte pin, byte mode, int numModes, int resetAfter);
    virtual byte readMode();
    virtual byte getMode();
    virtual void resetAfter(int someTime);
  private:
    byte MYcurrentMode = 0;
    int MYnumModes;
    int MYresetAfter;
    bool MYresetAllowed = false;
    unsigned long MYchrono = millis();
#endif
};//Mode--------------------------------------------------------------

//=============================================================================Encoder
//Constructor: (Does not Inherit, but uses two Contact objects)
//  pinA: the Arduino pin on which the encoders' pin A is attached
//  pinB: the Arduino pin on which the encoders' pin B is attached
//setModes():
//  Both modes defaults to PULLUP. Use before .begin() if PULLDOWN is required
//  modeA: either PULLUP or PULLDOWN depending on the wiring for pin A
//  modeB: either PULLUP or PULLDOWN depending on the wiring for pin B
//stepsPerClick():
//  Encoders can have 2 or 4 steps per click (Defaults to 4)
//begin();
//  Calls .begin() for the two Contacts
//getRotation():
//  Returns 0 if no rotation, CW (1) or CCW (-1)
//getCount():
//  Returns the contents of the counter. (Automaticaly updated en every read)
//setCount():
//  Allows to change the value of the counter
//resetCount():
//  Allows to set the counter to 0
//------------------------------------------------------------------------------
class Encoder : public Contact{
  public:
    Encoder();
    Encoder(byte pinA, byte pinB);
    virtual void setPins(byte pinA, byte pinB);
    virtual void setModes(byte modeA, byte modeB);
    virtual void stepsPerClick(byte stepsPerClick);
    virtual void begin();
    int getRotation();
    int getCount();
    void setCount(int value);
    void resetCount();
  private:
    int process(byte status);
    int count;
    int rotation();
    Contact MYpinA;
    Contact MYpinB;
    byte MYstepsPerClick = 4;
};
