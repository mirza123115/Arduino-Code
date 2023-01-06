#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
	// initialize the LCD
	lcd.begin();

	// Turn on the blacklight and print a message.
  lcd.backlight();
  Serial.begin(9600);
  //pinMode(A5,OUTPUT) ;
}

void loop()
{

  /*int x =analogRead(A4) ;
  Serial.println(x);*/
  
 
  lcd.setCursor(0,0);
  lcd.print("hi i am Emon");
  
  lcd.setCursor(0,1);
  lcd.print("i am EEE engineer");
 
  delay(5000);
  
  lcd.clear();

   lcd.setCursor(0,0);
  lcd.print("i work in intel");
  lcd.setCursor(0,1);
  lcd.print("i degien processor");
  delay(5000);
 
  
  lcd.clear();
 
	// Do nothing here...
}
