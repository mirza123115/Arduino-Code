//Count Display via Overflow Interrupt
//====================================
#include <Wire.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(128, 64, &Wire, 4);
volatile int i=0;
//=============================================================================
void setup()
{
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  
  //programming timer1 for overflow interrupt
  noInterrupts();
  TCCR1A = 0;             //initialize timer1
  TCCR1B = 0;
  TCCR1B |= 0b00000100;   //256 prescaler
  TIMSK1 |= 0b00000001;   //enable overflow interrupt
  interrupts();
}
//=============================================================================
ISR(TIMER1_OVF_vect)  //timer overflow ISR: update counter
{
  i++; if(i==100) i=0;
}
//=============================================================================
void loop()
{
  display.setTextColor(WHITE); display.clearDisplay();
  display.setTextSize(2); display.setCursor(0,0); display.println(" Overflow");
  display.setTextSize(6); display.setCursor(25,20); display.print(i);
  display.display();
}
