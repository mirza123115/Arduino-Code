#include <EEPROM.h>
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
byte a=0x00;
byte x=0;
while(a<0xFF)
{
  a++;
 x++;
  if (a==254)
  {a=0;}
  //EEPROM.write(a,x);
  delay(10);
  Serial.println(EEPROM.read(a));
  // Serial.println(a);
}
}

void loop() {
  // put your main code here, to run repeatedly:

}
