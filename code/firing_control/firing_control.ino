#define tiggering_signal_pin 3
#define interrupt_signal_pin 2
int pot_value;
int firing_time;

void setup() 
{
  pinMode(tiggering_signal_pin,OUTPUT);
  pinMode(interrupt_signal_pin,INPUT);
  attachInterrupt(digitalPinToInterrupt(interrupt_signal_pin),ISR_firing,RISING);
}

void loop(){ 

  digitalWrite(tiggering_signal_pin,LOW);//initially all signal is given as Low. 

  pot_value=analogRead(A0);
  firing_time=map(pot_value,0,1023,10,10000);//half cycle length is 10ms of sin wave.
}
void ISR_firing()
{
  delayMicroseconds(firing_time);
  digitalWrite(tiggering_signal_pin,HIGH);
  delayMicroseconds(1000);
  digitalWrite(tiggering_signal_pin,LOW);
}
