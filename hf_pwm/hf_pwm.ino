
/*void setup()
{
    pinMode(11, OUTPUT);  //enable G2 of Fig-10.3; do it using pinMode() function.
    //------------------------
    bitSet(TCCR2A, COM2A1); //keep PWM signal HIGH at start (non-inverting); do it using TCCR2A Reg.
    bitClear(TCCR2A, COM2A0);
    //------------------------
    bitSet(TCCR2A, WGM20); //select Mode-3 fast PWM using WGM bits of TCCR2A/TCCR2B Reg.
    bitSet(TCCR2A, WGM21);
    bitClear(TCCR2B, WGM22);
    //-------------------------
    OCR2A = 16; //put 16 into OCR2A for initial 1 us ON-time. (clkTC2 = 16 MHz) ; (16MHz/1)*1 us = 16
    //-------------------------
    bitSet(TCCR2B, CS20); //Start TCNT2 with 16 MHz; do it using TCCR2B Register
    bitClear(TCCR2B, CS21);
    bitClear(TCCR2B, CS22);
    //-------------------------
}

void loop()
{
    while(bitRead(TIFR2, OCF2A) != HIGH)   //checking if ON-times has ended or not
    {
         ; //wait until ON-time/duty cycle ends of the PWM
     }
     bitSet(TIFR2, OCF2A);    //clear OCF2A flag
     OCR2A = OCR2A + 16;  //augment duty cycle by 1 us
     delay(40);                 //wait for 4 sec to see the next change in duty cycle
}

*/

void setup()
{
    
    //---L1: Our desired PWM signal (waveform-4 of Fig-10.4) will appear on DPun-11 of Fig-10.3. So, the
    //---direction of DPin-11 must be made output. This is done by the following code:
    pinMode(11, OUTPUT);  
    
    //---L2: Our desire PWM signal starts with HIGH state -- it is "non-inverting" mode. To do it,
    //---we put 1, 0 into the COM2A1, COM2A0 bits of TCCR2A Register of Fig-10.5. the codes are:  
    bitSet(TCCR2A, COM2A1);  
    bitClear(TCCR2A, COM2A0);

    //---L3: To get our desired PWM signal (waveform-4 of Fig-10.4), we must activate Mode-3 operation
    //---for Ch-A. This is done but putting 0, 1, 1 into WGM22, WGM21, WGM20 bits of TCCR2B and
    //---TCCR2A Registers. The codes are:
    bitClear(TCCR2A, WGM22); //select Mode-3 fast PWM using WGM bits of TCCR2A/TCCR2B Reg.
    bitSet(TCCR2A, WGM21);
    bitSet(TCCR2A, WGM20);
 
    //---L4: Let us set the intial ON-time (duty cycle of PWM) at 25% (4 us). This is done by putting some
    //---"quantity"  into 8-bit OCR2A Register (see waveform-1 of Fig-10.4). (T = 1/62500 = 16 us). What
    //---is value of this "quantity"?The OCR2A register can hold 0 to 255 for 0% tp 100% duty cycle.
    //---Therefore, we have to store 255/4 = 64 into OCR2A register. The code is:
    OCR2A = 1;     //timeDelay for 64 counts is: (16/256)*64 = 4 us)
    
    //---L5: We want 62.5 kHZ repetitions for our PWM signal. To do it, we put 0, 0, 1 into CS22, CS21,
    //---CS20 bits of TCCR2B Register. The codes are: (When these bits are loaded, the TC2 starts and
    //---PWM signal appears on DPin-11.)
    bitClear(TCCR2B, CS22); //Start TCNT2 with 16 MHz; do it using TCCR2B Register
    bitClear(TCCR2B, CS21);
    bitSet(TCCR2B, CS20);

    //---L6: Connect oscilloscope at DPin-11 and observe the PWM signals as depicted in Fig-10.7.
  Serial.begin(9600);
}
int x=0;
float t=0;
void loop()
{
  
  x=x+1.1;
  t=t+.0002;
  //OCR2A = abs(x);
  int k=255*(sin(314.16*t));
  Serial.println(k);
  OCR2A = 255*abs(sin(314.16*t));
  delay(10);  
  /*if (x==255)
  {
    x=-x;
  }*/

  if (t>=.02)
  {
   t=0;
  }
  
    //---Write codes to sense motor speed and then put new value into OCR2A regsiter to get new duty
    //---cycle of the PWM signal. This will help to bring the motor speed at the desired level.
}
