#include<SoftwareSerial.h>  //suart
SoftwareSerial SUART(2, 3);  //SRXD = DPin-2, STXD = DPin-3 ;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);//UART
SUART.begin(9600); //SUART
  // put your main code here, to run repeatedly:
while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}
char  y;
float x=0;
byte d=0x00;
void loop() {
  
   x+=.001;
  if (x>=6.28)
  {x=0;}
  int v=10000*sin(100*x);
  byte a=analogRead(A3);
  byte b=analogRead(A2);
   SUART.print(a+b);
   delay(5);
   SUART.write('\n');
  //Serial.print("I received: ");
    Serial.println(a+b);
     

   /* d++;
    Serial.write(d);
     SUART.print(d);
     delay(5);
     //SUART.print("B");
      SUART.write('\n'); 
    
    if (d>=127)
  {d=0x00;}*/
     
/* int n=Serial.available() ;
  if (n> 0) {
    // read the incoming byte:
  y = Serial.read();
  SUART.write(y);
  //Serial.print("I received: ");
    Serial.print(y);
    delay(5);
}*/
}
/*void serialEvent()
{
    y = Serial.read();
  SUART.write(y);

}
*/
