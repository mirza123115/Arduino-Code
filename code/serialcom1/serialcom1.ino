#include<Wire.h>             //i2c contains ready-made functions/methods to do varieties of tasks
#include<SPI.h>    //spi contains ready-made routines
#include<SoftwareSerial.h>  //suart
#include <LiquidCrystal_I2C.h>
SoftwareSerial SUART(2, 3);  //SRXD = DPin-2, STXD = DPin-3 ; S stands for Software
//SoftwareSerial mySerial(2, 3); // RX, TX
LiquidCrystal_I2C lcd(0x27,16,2); 


void setup() {
  SPI.begin();  //SPI Port is created and 
Wire.begin();//I2C Interface Module is connected with SDA and SCL lines
Serial.begin(9600);//UART
 while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

SUART.begin(9600); //SUART

// initialize the LCD
 lcd.begin();
  // Turn on the blacklight and print a message.
  lcd.backlight();
//  lcd.init();
  lcd.clear();
   lcd.backlight();
   pinMode(13,OUTPUT);
}
char mon[]="emon";
void loop() {
  
  /*1111UART
  int x=0x0908;
 int y=lowByte(x);
 Serial.println(y); 
*/

/*222222i2c
 * Wire.beginTransmission(0x52);       //START condition & slaveAddress queued in BUFFer
byte busStatus = Wire.endTransmission();   //above codes and then STOP asserted
if(busStatus != 0x00)                                 //Status Word 0x00 is generated or not
{
  Serial.print("Slave is not found on theI2C Bus…!");
  while(1);                                                                  //wait for ever
}
  Serial.println("Slave is found on the I2C Bus.");
*/
  
int n=Serial.available() ;
 if (n> 0) {
    // read the incoming byte:
char  y = Serial.read();
int  z=atoi(y);
 if (z ==1)
  {
    digitalWrite(LED_BUILTIN,HIGH);
    delay(1000);
  }

    // say what you got:
    Serial.print("I received: ");
    Serial.println(y);
    delay(5);

    lcd.setCursor(1,0);
  lcd.print(y);
//int  z=atoi(y);
//int z = Serial.parseInt();
 
  }

  
}
