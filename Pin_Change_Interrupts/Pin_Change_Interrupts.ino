//===========================
//Pin Change Interrupts (PCI)
//===========================
#define GREENLED  12
#define BLUELED   10
#define REDLED    8
#define WHITELED  6
//===========================================================================
void setup()
{
  pinMode(4,INPUT); pinMode(13,INPUT);
  pinMode(GREENLED,OUTPUT); pinMode(BLUELED,OUTPUT);
  pinMode(REDLED,OUTPUT); pinMode(WHITELED,OUTPUT);

  //enabling PCI
  PCICR  |= 0b00000001; //enable port B for PCI
  PCMSK0 |= 0b00100000; //enable INT5 attached to pin D13 (SW1)
  PCICR  |= 0b00000010; //enable port C for PCI
  PCMSK1 |= 0b00100000; //enable INT13 related to pin A5 (SW2)
  PCICR  |= 0b00000100; //enable port D for PCI
  PCMSK2 |= 0b00010000; //enable INT20 related to pin D4 (sensor)
}
//===========================================================================
void loop()
{
  digitalWrite(BLUELED,LOW);digitalWrite(REDLED,LOW);digitalWrite(WHITELED,LOW);
  digitalWrite(GREENLED,HIGH); delay(100);
  digitalWrite(GREENLED,LOW); delay(100);
}
//===========================================================================
//ISR for INT5 (SW1 on pin D13)
ISR(PCINT0_vect)
{
  for(int i=1;i<=50;i++)
  {
    digitalWrite(BLUELED,HIGH); delayMicroseconds(16000);
    digitalWrite(BLUELED,LOW); delayMicroseconds(16000);
  }
}
//===========================================================================
//ISR for INT13 (SW2 on pin A5)
ISR(PCINT1_vect)
{
  for(int i=1;i<=50;i++)
  {
    digitalWrite(REDLED,HIGH); delayMicroseconds(16000);
    digitalWrite(REDLED,LOW); delayMicroseconds(16000);
  }
}
//===========================================================================
//ISR for INT20 (sensor on D4)
ISR(PCINT2_vect)
{
  for(int i=1;i<=50;i++)
  {
    digitalWrite(WHITELED,HIGH); delayMicroseconds(16000);
    digitalWrite(WHITELED,LOW); delayMicroseconds(16000);
  }
}
