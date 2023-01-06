void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(A0,OUTPUT);

}
void loop()
{
for (float x=0;x<=2*3.1416;x=x+.1)
{
  float y=255*sin(x);
  Serial.println(y);
 
  analogWrite(A0,y);
  
}
}
