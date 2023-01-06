void setup() {
  // put your setup code here, to run once:
pinMode(8,INPUT_PULLUP);
pinMode(9, OUTPUT);
pinMode(10, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
int sensorValue = digitalRead(8);
if (sensorValue == HIGH)
{
digitalWrite(9, HIGH); 
digitalWrite(10, LOW);
delay(9);
digitalWrite(9, LOW); 
digitalWrite(10,HIGH);
  delay(9); 
}
else {
   digitalWrite(9, LOW);
   digitalWrite(10, LOW);
  }
}
