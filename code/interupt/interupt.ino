void setup()
{

pinMode(13, OUTPUT);      //to drive L (built-in LED of UNO
digitalWrite(13, LOW);      //L is initially OFF
//---------------------------------------------------------------
pinMode(8, OUTPUT);      //to drive LED1 of ISRINT0 routine
digitalWrite(8, LOW);      //LED1 is initially OFF
  
//---------------------------------------------------------------
pinMode(2, INPUT);  //internal pull-up is connected with DPin-2/INT0-pin
attachInterrupt(digitalPinToInterrupt(2),ISR_fun,RISING);
}
byte counter = 3;    //LED1 of ISRINT0 routine be executed for 3 times via the loop() function.
volatile bool flag = false;

void loop()
{

  if (flag == false)    //interrupt has not occurred; keep blinking L
  {
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
    delay(1000);
  }
  else    //interrupt has arrived at INT0-pin via DPin-2; blink LED1 for 3 times
  {
    do
    {
      //-------------------
      digitalWrite(8, HIGH);
      delay(2000);
      digitalWrite(8, LOW);
      delay(2000);
      //-------------------
      counter--;
    }
    while (counter != 0);
    flag = false;
    counter = 3;
  }
}
  
    
    void ISR_fun()
{
   flag = true;   //flag will allow to blink LED1 for 3 times at 2-sec interval using delay() function
}
