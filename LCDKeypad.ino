#include <LiquidCrystal.h>
#include <LCDKeypad.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
LCDKeypad keypad(0);                // pin A0 controls the keypad

const int backLightPin = 10;
const boolean serialPrint = 1;      // change to 1 for read out to Serial Monitor
int lcd_key = -1;

void setup()
{
  if ( serialPrint == 1 )
  {
    Serial.begin(9600);
  }
  pinMode(backLightPin,OUTPUT);     // control blacklight brightness with PWM
  analogWrite(backLightPin,100);
  lcd.begin(16, 2);                 // start the library
  lcd.setCursor(0,0);
  lcd.print("Push the buttons");    // print a simle message
}

void loop()
{
  lcd.setCursor(9,1);
  lcd.print(millis()/1000);
  lcd.setCursor(0,1);
  lcd_key = keypad.read();
  //Serial.println(lcd_key);
  switch (lcd_key)
  {
    case Right:
    {
      lcd.print("RIGHT");
      if (serialPrint == 1)
      {
        Serial.println("Right");
      }
      break;
    }
    case Left:
    {
      lcd.print("LEFT  ");
      if (serialPrint == 1)
      {
        Serial.println("Left");
      }
      break;
    }
    case Up:
    {
      lcd.print("UP    ");
      if (serialPrint == 1)
      {
        Serial.println("Up");
      }
      break;
    }
    case Down:
    {
      lcd.print("DOWN  ");
      if (serialPrint == 1)
      {
        Serial.println("Down");
      }
      break;
    }
    case Select:
    {
      lcd.print("SELECT");
      if (serialPrint == 1)
      {
        Serial.println("Select");
      }
      break;
    }
    case None:
    {
      //lcd.print("NONE  ");
      if (serialPrint == 1)
      {
        //Serial.println("None");
      }
      break;
    }
  }
}