//Input Capture Interrupt
//=======================
#include <Wire.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(128, 64, &Wire, 4);
volatile unsigned int previous_capture = 0;
volatile unsigned int current_capture = 0;
//============================================================================
void setup()
{
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  
  //programming timer1 for input capture interrupt
  noInterrupts();
  TCCR1A = 0;             //initialize timer1 mode
  TCCR1B = 0;
  TCCR1B |= 0b11000101;   //set 1024 prescaler, rising edge, noise canceler
  TIMSK1 |= 0b00100000;   //enable input capture interrupt
  TCNT1 = 0;              //initialize timer/counter1 register
  interrupts();
}
//============================================================================
ISR(TIMER1_CAPT_vect)  //input capture interrupt ISR
{
  previous_capture = current_capture;
  current_capture = ICR1;
}
//============================================================================
void loop()
{
  display.setTextColor(WHITE); display.clearDisplay();
  display.setTextSize(2); display.setCursor(0,0); display.print("  Capture");
  display.setCursor(0,18); display.print(" Interrupt");
  display.setTextSize(3); display.setCursor(20,42); display.print(input_capture);
  display.display();
}
