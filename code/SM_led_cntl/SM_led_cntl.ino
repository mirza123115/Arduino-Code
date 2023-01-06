//sketch created by Akshay Joseph
char x;
void setup() {
 Serial.begin(9600);
 pinMode(13,OUTPUT);

}

void loop() {
while(Serial.available()>0){
x= Serial.read();
  
  Serial.println(x);
  if (x=='1'){
  digitalWrite(13,HIGH);
  }
  else if (x=='2'){
  digitalWrite(13,LOW);
  } 
  }
}
