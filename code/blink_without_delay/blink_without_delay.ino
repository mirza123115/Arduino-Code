void setup()
{
  pinMode(13,OUTPUT);
}
byte output = HIGH;
void loop()
{
   unsigned long prMillis = millis();  //get elapsed time since you have uploaded sketch
   while(millis() - prMillis < 1000)     //1 sec has not yet elapsed
   {
       digitalWrite(13, output);         //L remains ON for 1-sec
   }
   output = !output;                      //now output = LOW
}
