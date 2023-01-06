void setup() {
  // put your setup code here, to run once:
DDRD=0xFF;


}
int mySensVals[10]  ={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
int x=0;
void loop() {
  
  x=x+1;
  // put your main code here, to run repeatedly:
  PORTD=mySensVals[x];
  delay(300);
if(x>=9)
{x=0;}
}
