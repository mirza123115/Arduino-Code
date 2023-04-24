//External Interrupts
//===================
#define SW        2
#define SENSOR    3
#define BLUELED   12
#define REDLED    9
#define YELLOWLED 6
//===================================================================
void setup()
{
  pinMode(SENSOR,INPUT); pinMode(BLUELED,OUTPUT);
  pinMode(REDLED,OUTPUT); pinMode(YELLOWLED,OUTPUT);
  attachInterrupt(0,ISR_SW,RISING); attachInterrupt(1,ISR_SENSOR,RISING);
}
//===================================================================
void loop()
{
  digitalWrite(REDLED,LOW); digitalWrite(YELLOWLED,LOW);
  digitalWrite(BLUELED,HIGH); delay(500);
  digitalWrite(BLUELED,LOW); delay(500);
}
//===================================================================
void ISR_SW()
{
  for(int i=1;i<=50;i++)
  {
    digitalWrite(REDLED,HIGH); delayMicroseconds(16000);
    digitalWrite(REDLED,LOW); delayMicroseconds(16000);
  }
}
//===================================================================
void ISR_SENSOR()
{
  for(int i=1;i<=50;i++)
  {
    digitalWrite(YELLOWLED,HIGH); delayMicroseconds(16000);
    digitalWrite(YELLOWLED,LOW); delayMicroseconds(16000);
  }
}
