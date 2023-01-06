void setup() {
  // put your setup code here, to run once:
  DDRD=0XFF;
  pinMode(10,OUTPUT);
   pinMode(11,OUTPUT);
}
void loop() {
  PORTD=0X66;
   int x=random(1,6);
   int y=x+20;
   PORTD=0X5B;
   digitalWrite(11,LOW);
   digitalWrite(10,HIGH);
   delay(10);
   
   PORTD=0X4F;
   digitalWrite(11,HIGH);
   digitalWrite(10,LOW);
    delay(10);

  // put your main code here, to run repeatedly:

}
