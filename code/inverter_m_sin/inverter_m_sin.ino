void setup() {
  // put your setup code here, to run once:
pinMode(9, OUTPUT);
pinMode(10, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(9, LOW); 
digitalWrite(10, LOW);
delay(2);
digitalWrite(9, HIGH); 
digitalWrite(10, LOW);
  delay(6); 
  digitalWrite(9, LOW); 
digitalWrite(10, LOW);
delay(4) ;                    

digitalWrite(9, LOW); 
digitalWrite(10, HIGH);
  delay(6); 
  digitalWrite(9, LOW); 
digitalWrite(10, LOW);
delay(2) ;  
  
}
