void setup() {
  // put your setup code here, to run once:
pinMode(11,OUTPUT);
Serial.begin(9600);
//Serial.println(2);
}

void loop() {
  // put 9your main code here, to run repeatedly:
 //x=x+.1;
//float y=sin(x)+sin(2*x);
int x=analogRead(A5);
Serial.println(x);
//Serial.println(255*y);
//delay(10);
}
