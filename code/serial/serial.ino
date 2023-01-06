#include<Wire.h>             //i2c contains ready-made functions/methods to do varieties of tasks
#include<SPI.h>    //spi contains ready-made routines
#include<SoftwareSerial.h>  //suart
#include <LiquidCrystal_I2C.h>
SoftwareSerial SUART(2, 3);  //SRXD = DPin-2, STXD = DPin-3 ; S stands for Software
//SoftwareSerial mySerial(2, 3); // RX, TX
LiquidCrystal_I2C lcd(0x27,16,2); 


void setup() {
//SPI.begin();  //SPI Port is created and 
Wire.begin();//I2C Interface Module is connected with SDA and SCL lines
Serial.begin(9600);//UART
SUART.begin(9600); //SUART

 while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

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
char data[10];
char  y;
void loop() {
  
  /*1111UART
  int x=0x0908;
 int y=lowByte(x);
 Serial.println(y); 
*/

/*222222i2c
 * Wire.beginTransmission(0x52);       //START condition & slaveAddress queued in BUFFer
byte busStatus = Wire.endTransmission();   //above codes and then STOP asserted
while(busStatus != 0x00)                                 //Status Word 0x00 is generated or not
{
  Serial.print("Slave is not found on theI2C Bus…!");
                                                                 
}
  Serial.println("Slave is found on the I2C Bus.");
*/
  
int n=Serial.available() ;
 if (n> 0) {
    // read the incoming byte:
  y = Serial.read();
  if (y =='1')
  {
    digitalWrite(13,HIGH);

  }
     else if (y=='2'){
  digitalWrite(13,LOW);
  } 
  

    // say what you got:
    Serial.print("I received: ");
    Serial.println(y);
    delay(5);

    lcd.setCursor(7,0);
  lcd.write(y);

 
  }

  
}




/*#include<SPI.h>
byte myData[] = {0x00, 0x00, 0x00, 0x00};
void setup()
{
  Serial.begin(9600);
  SPI.begin();
  delay(100);
  SPI.setClockDivider(SPI_CLOCK_DIV16);//1 MBits/s
  //pinMode(SS, OUTPUT);
  digitalWrite(SS, LOW);  //Slave is selected
  //--------------------
}

void loop()
{
  for (int i = 0; i < 4; i++)
  {
    myData[i] = SPI.transfer(myData[i]);
    delayMicroseconds(100); //allows Slave to process received byte
    Serial.println(myData[i], HEX);  //shows: 0xAB
  }
  long x = (long)myData[1] << 24 | (long)myData[2] << 16 | (long)myData[3] << 8 | (long)myData[0];
  Serial.println(x, HEX); //shows: 0x12345678
  Serial.println("======================");
  delay(1000);  //test interval
}

//slave sketch...........................
#include<SPI.h>
int i = 0;
byte myData[] = {0x12, 0x34, 0x56, 0xAB};

void setup()
{
  Serial.begin(9600);
  SPI.setClockDivider(SPI_CLOCK_DIV16);//
  pinMode(SS, INPUT_PULLUP);  // ensure SS stays high for now
  pinMode(MISO, OUTPUT);
  SPCR |= _BV(SPE);
  SPCR |= !(_BV(MSTR)); //Arduino is Slave
  SPI.attachInterrupt();   //interrupt logic is enabled
}

void loop()
{

}

ISR(SPI_STC_vect)
{
  SPDR = myData[i]; //places 0x12, then 0x34, then 0x56, then 0xAB
  i++;
  if (i == 4)     //4-byte data are sent
  {
    i = 0;          //array pointer is reset
  }
}




//two side transmission in spi ................................................master
#include<SPI.h>

void setup()
{
  Serial.begin(9600);
  SPI.begin();
  delay(100);
  SPI.setClockDivider(SPI_CLOCK_DIV16);//
  //pinMode(SS, OUTPUT);
  digitalWrite(SS, LOW);
  //--------------------
  

}

void loop()
{
  SPDR = 0x93;
  while (bitRead(SPSR, SPIF) != HIGH)
  {
    ;
  }
  byte x = SPDR;
  bitSet(SPSR, SPIF);
  Serial.println(x, HEX); //shows: 0x87
  while (1);
}


//slave........
#include<SPI.h>

void setup()
{
  Serial.begin(9600);
  SPI.setClockDivider(SPI_CLOCK_DIV16);//
  pinMode(SS, INPUT_PULLUP);  // ensure SS stays high for now
  pinMode(MISO, OUTPUT);
  SPCR |= _BV(SPE);
  SPCR |= !(_BV(MSTR)); //Arduino is Slave
  //SPCR |= _BV(SPIE);
  //SPI.attachInterrupt();
  //SPDR = myData[0];
  SPDR = 0x87;

}

void loop()
{
  while (bitRead(SPSR, SPIF) != HIGH)
  {
    ;
  }
  byte x = SPDR;
  bitSet(SPSR, SPIF);
  Serial.println(x, HEX); //shows: 0x93
}
*/
