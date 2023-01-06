void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);
pinMode(7,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
int x=analogRead(A0);
Serial.println(x);
if (x<100)
{
  digitalWrite(7,1);
  delay(1000);
}
else
digitalWrite(7,0);

}
