/*
  LCDKeypad.h - Library for reading key inputs from LCD Keypad
  Debounce and repeat delay implemented
*/

#ifndef LCDKeypad_h
#define LCDKeypad_h

#include "Arduino.h"
//#include "LiquidCrystal.h"

#define Right  0 
#define Up     1 
#define Down   2 
#define Left   3 
#define Select 4 
#define None   5 

class LCDKeypad
{
  public:
    LCDKeypad(byte _keypadPin);
	int read();
  private:
    const int _minPressTime = 70;
	const int _repeatDelayTime = 500;
	byte _keypadPin;
	int interpretKey(int _rawKey);
	int _rawKey;
	byte _keyReading;
    byte _keyPrevious;
    byte _keyRegistered;
    byte _keyRegisteredPrevious;
    long _beginDebounceMillis;
    bool _resetDebounceMillis;
    long _beginRepeatDelayMillis;
    bool _resetRepeatDelayMillis;
};

#endif
 