#include "Arduino.h"
#include "LCDKeypad.h"

LCDKeypad::LCDKeypad(byte keypadPin)
{
  _keypadPin = keypadPin;          // read input from program calling this library into a private value
  
  //_minPressTime = 70;            // change these values in LCDKeypad.h
  //_repeatDelayTime = 500;        // change these values in LCDKeypad.h
  _keyRegistered = None;
  _keyRegisteredPrevious = None;
  _beginDebounceMillis = 0;
  _resetDebounceMillis = 1;
  _beginRepeatDelayMillis = 0;
  _resetRepeatDelayMillis = 1;
    
  pinMode(_keypadPin, INPUT_PULLUP);
}
LCDKeypad::~LCDKeypad() {}

int LCDKeypad::read() 
{ 
  //  Debounce Routine
  /*  Three possible scenarios here:
   *    1. a) A BUTTON IS PRESSED for the b) FIRST TIME -> start counting delay
   *    2. The a) SAME button  is held for b) MORE THAN DEBOUNCE DELAY
   *      2.1   a) NOT a repeat of the last button registered -> reset counting and return cursor
   *      2.2   a) Is a repeat of the last button registered for the b) FIRST TIME -> start counting repeat key delay
   *      2.3   a) Still is a repeat of the last button registered is held for b) MORE THAN REPEAT KEY DELAY -> reset counting repeat key delay and return cursor      
   *    3. No buttons are pressed (including buttons released before delay) -> reset counting both debounce and repeat key delay
  */
  _rawKey = analogRead(_keypadPin);
  _keyReading = interpretKey(_rawKey);
  
  // 1. a) A BUTTON IS PRESSED for the b) FIRST TIME -> start counting delay
  if ( _keyReading != None && _resetDebounceMillis == 1 && _resetRepeatDelayMillis == 1 )
  {
    _beginDebounceMillis = millis();
    _resetDebounceMillis = 0;
    _keyPrevious = _keyReading;
    _keyRegistered = None;				// Button is not registered yet. Do not return anything
    /*
	Serial.println();
    Serial.print("Key ");
    Serial.print(_keyReading);
    Serial.print(" pressed at ");
    Serial.print(_beginDebounceMillis);
    Serial.print("ms   ");
	*/
  }
  // 2. The a) SAME button  is held for b) MORE THAN DEBOUNCE DELAY
  if ( _keyReading == _keyPrevious && millis() > _beginDebounceMillis + _minPressTime )
  {
    // 2.1  a) NOT a repeat of the last button registered -> reset counting and return cursor
    if (_keyReading != _keyRegisteredPrevious )
    {
      _resetDebounceMillis = 1;
      _keyRegistered = _keyReading;
      _keyRegisteredPrevious = _keyRegistered;
      /*
	  Serial.print("Key ");
      Serial.print(_keyRegistered);
      Serial.print(" registered  at ");
      Serial.print(millis());
      Serial.print("ms   ");
	  */
    }
      
    //  2.2 a) Is a repeat of the last button registered for the b) FIRST TIME -> start counting repeat key delay
    else if ( _keyReading == _keyRegisteredPrevious && _resetRepeatDelayMillis == 1 )
    {
      _beginRepeatDelayMillis = millis();
      _resetDebounceMillis = 0;                  // turn this to 0 so when key is held and repeated it will not trigger scenario 1 again
      _resetRepeatDelayMillis = 0; 
      _keyRegistered = None;			// repeat key not registered yet! Do not return any button
	  /*
      Serial.print("Key ");
      Serial.print(_keyReading);
      Serial.print(" repeat detected at ");
      Serial.print(_beginRepeatDelayMillis);
      Serial.print("ms   ");
	  */
    }
    // 2.3  a) Still is a repeat of the last button registered is held for b) MORE THAN REPEAT KEY DELAY -> reset counting repeat key delay and return cursor
    else if ( _keyReading == _keyRegisteredPrevious && millis() > _beginRepeatDelayMillis + _repeatDelayTime )
    {
      _resetRepeatDelayMillis = 1;
      _keyRegistered = _keyReading;
      _keyRegisteredPrevious = _keyRegistered;
      /*
	  Serial.print("Key ");
      Serial.print(_keyRegistered);
      Serial.print(" repeat allowed  at ");
      Serial.print(millis());
      Serial.print("ms   ");
	  */
    }
  }
  // 3. No buttons are pressed (including buttons released before delay) -> reset counting
  if ( _keyReading == None )
  {
    _resetDebounceMillis = 1;
    _resetRepeatDelayMillis = 1;
    _keyRegistered = None;
    _keyRegisteredPrevious = None;
    /*
    Serial.println();
    Serial.println("No key detected");
    */
  }
  return _keyRegistered;
}


int LCDKeypad::interpretKey(int _inputRawKey)
{ 
  if (_inputRawKey > 1000)  return None;    // Most likely option! Put 1st for speed
  if (_inputRawKey < 50)    return Right;
  if (_inputRawKey < 195)   return Up;
  if (_inputRawKey < 380)   return Down;
  if (_inputRawKey < 555)   return Left;
  if (_inputRawKey < 790)   return Select;
  return None;        // If everything fails, return none
}
