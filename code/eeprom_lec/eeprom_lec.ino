#include <EEPROM.h>

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
/*EECR=0x00;
EECR=EECR |0b00000100;
EEARH=0x02;
EEARL=0x34;
EEDR=0x23;
EECR=EECR |0b00000010;
while(bitRead(EECR,1)!=LOW)
{
  ;
}
EEARH=0x02;
EEARL=0x34;
EECR =0b00000001;
byte x=EEDR;
EECR=0x00;*/
//  EEPROM.clear();
byte a=0x00;
while(a<0xFF)
{
  a++;
  //EEPROM.write(a,a);
  Serial.println(EEPROM.read(a));
}
/*EEPROM.write(0x234,0xFE);
byte x=EEPROM.read(0x234);
Serial.println(x);*/

}



void loop() {
  // put your main code here, to run repeatedly:

}
