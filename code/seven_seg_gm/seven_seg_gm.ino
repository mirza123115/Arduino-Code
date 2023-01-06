#include "SevSeg.h"
SevSeg sevseg;
byte numDigits = 4;
byte digitPins[] = {A0, A1, A2, A3};//DP0, DP1, DP2, DP3
byte segmentPins[] = {8, 9, 10, 11, 12, 13, 6, 7};//a, b, c, ..., g, p from left
bool resistorsOnSegments = false;
byte hardwareConfig = COMMON_CATHODE;

void setup()
{
  Serial.begin(9600);
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(30);
  analogReference(INTERNAL);
}

void loop()
{
  unsigned long prMillis = millis();
  while (millis() - prMillis < 2000)//temp refreshed at 2-sec interval
  {
    sevseg.refreshDisplay();
  }

  float temp = 100 * ( 1.1 / 1023) * analogRead(A4);//31.76
  sevseg.setNumber(temp, 2);//decimal before 2-digit from right
}
