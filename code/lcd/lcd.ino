

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
 // initialize the LCD
 lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  Serial.begin(9600);
  //pinMode(A5,OUTPUT) ;
  //lcd.init();
  lcd.clear();
 
}


void loop()
{
    
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("hello everyone");
  lcd.setCursor(1,1);
  lcd.print("konichiwaa");
 
}
