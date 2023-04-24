//Blinking LED using Compare Match Interrupt
//==========================================
#include <Wire.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(128, 64, &Wire, 4);
#define redLED  8
#define blueLED 2
//==========================================================================
void setup()
{
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  pinMode(redLED, OUTPUT); pinMode(blueLED, OUTPUT);
  
  //programming timer1 for compare match interrupt
  noInterrupts();
  TCCR1A = 0;             //initialize timer1
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 15625;          //store in output compare register: 16MHz/256/4Hz
  TCCR1B |= 0b00001100;   //CTC mode and 256 prescaler
  TIMSK1 |= 0b00000010;   //enable timer compare interrupt
  interrupts();
}
//==========================================================================

ISR(TIMER1_COMPA_vect)  //timer compare ISR: toggle red LED pin
{
  digitalWrite(redLED, digitalRead(redLED)^1);
}
//==========================================================================
void loop()
{
  for(int i=1; i<=99; i++)
  {
    digitalWrite(blueLED,digitalRead(blueLED)^1); delay(1000);
    display.setTextColor(WHITE); display.clearDisplay();
    display.setTextSize(2); display.setCursor(0,0);
    display.println(" main code");
    display.setTextSize(6); display.setCursor(30,20); display.print(i);
    display.display();
  }
}
