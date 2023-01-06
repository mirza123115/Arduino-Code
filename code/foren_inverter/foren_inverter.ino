const unsigned char PS_16 = (1 << ADPS2);
const unsigned char PS_32 = (1 << ADPS2) | (1 << ADPS0);
const unsigned char PS_64 = (1 << ADPS2) | (1 << ADPS1);
const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
volatile int feedback = 0;
volatile int i = 1;
volatile int x = 0;
volatile int x2 = 0;
volatile int OK = 0;
int N = 20001;
volatile int runXTimes = 0;
volatile int XT = 0;
#define pulses 128
int sinPWM[pulses] =
{
0, 19, 38, 57, 76, 95, 114, 133, 152, 171, 190, 208, 226, 245, 263, 281, 298, 316, 333, 351, 368, 384, 401, 417, 433, 449,
465, 480, 495, 509, 524, 538, 552, 565, 578, 591, 603, 615, 627, 638, 649, 659, 669, 679, 688, 697, 705, 713, 721, 728,
734, 741, 746, 752, 757, 761, 765, 769, 772, 774, 776, 778, 779, 780, 780, 780, 779, 778, 776, 774, 772, 769, 765, 761,
757, 752, 746, 741, 734, 728, 721, 713, 705, 697, 688, 679, 669, 659, 649, 638, 627, 615, 603, 591, 578, 565, 552, 538,
524, 509, 495, 480, 465, 449, 433, 417, 401, 384, 368, 351, 333, 316, 298, 281, 263, 245, 226, 208, 190, 171, 152, 133,
114, 95, 76, 57, 38, 19
};
void setup() {
pinMode(10, OUTPUT);
pinMode(9, OUTPUT);
DDRB |= (1 << PB0);
DDRB |= (1 << PB4);
DDRB |= (1 << PB5);
ADCSRA &= ~PS_128;
ADCSRA |= PS_16; // Speed up ADC..
feedback = analogRead(A2);
ADCSRB |= 0b00000000; // set ADC into free mode...
feedback = map (feedback, 0 , 1024 , 10 , 100);
TCCR1A = 0; // undo the configuration done by...
TCCR1B = 0; // ...the Arduino core library
TCCR1A = 0b10100010;
TCCR1B = 0b00011001; // 20 Khz PWM on 9 and 10
ICR1 = 780;
}
void softstart () {
if (i > pulses && OK == 0) { // final value from vector for pin 6
i = 0; // go to first value of vector
OK = 1; //enable pin 10
// PORTB = (0 << PB4);
PORTB = (1 << PB0);
}
if (i > pulses && OK == 1) { // final value from vector for pin 5
i = 0; //go to firs value of vector
OK = 0; //enable pin 9
// PORTB = (0 << PB0);
// PORTB = (1 << PB4);
}
x = sinPWM[i]; // x take the value from vector corresponding to position i(i is zero indexed)
i = i + 1; // go to the next position
x2 = x / 100 * 20;
if (OK == 0) {
OCR1B = 0; //make pin 10 0
__asm__("nop\n\t");// "deadtime" bout 62us per nop call
__asm__("nop\n\t");// "deadtime" bout 62us per nop call
OCR1A = x2; //enable pin 9 to corresponding duty cycle
}
if (OK == 1) {
OCR1A = 0; //make pin 9 0
__asm__("nop\n\t");// "deadtime" bout 62us per nop call
__asm__("nop\n\t");// "deadtime" bout 62us per nop call
OCR1B = x2; //enable pin 10 to corresponding duty cycle
}
}
void settimers () {
cli();// stop interrupts
TCCR1A = 0; // undo the configuration done by...
TCCR1B = 0; // ...the Arduino core library
TCCR1A = 0b10100010;
TCCR1B = 0b00011001;
ICR1 = 780;
// 20 Khz PWM on 9 and 10 redo, not necessary i guess
TCCR0A = 0; //reset the value
TCCR0B = 0; //reset the value
TCNT0 |= 0; //reset the timer
TCCR0A = 0b10100010;
TCCR0B = 0b00000010;
OCR0A = 154; // compare match value
TIMSK0 |= (1 << OCIE0A); // enable interrupts
// Interrupt for SPWM pulses
TCCR2A = 0; //reset the value
TCCR2B = 0; //reset the value
TCNT0 |= 0; //reset the timer
TCCR2A = 0b10100010;
TCCR2B = 0b00000111;
OCR2A = 156; // compare match value
TIMSK2 |= (1 << OCIE2A); // enable interrupts
// Interrupt for Feedback line
sei();
}
ISR(TIMER0_COMPA_vect) { // interrupt when timer 1 match with OCR1A value
if (i > pulses && OK == 0) { // final value from vector for pin 6
i = 0; // go to first value of vector
OK = 1; //enable pin 10
// PORTB = (0 << PB4);
// PORTB = (1 << PB0);
}
if (i > pulses && OK == 1) { // final value from vector for pin 5
i = 0; //go to firs value of vector
OK = 0; //enable pin 9
// PORTB = (0 << PB0);
// PORTB = (1 << PB4);
}
x = sinPWM[i]; // x take the value from vector corresponding to position i(i is zero indexed)
i = i + 1; // go to the next position
x2 = x / 100 * feedback; // adjust total to modulate pulse according to feedback...
if (OK == 0) {
OCR1B = 0; //make pin 10 0
__asm__("nop\n\t");
__asm__("nop\n\t");
OCR1A = x2; //enable pin 9 to corresponding duty cycle
}
if (OK == 1) {
OCR1A = 0; //make pin 9 0
__asm__("nop\n\t");
__asm__("nop\n\t");
OCR1B = x2; //enable pin 10 to corresponding duty cycle
}
TIFR0 = (1 << OCF0A);
}
ISR(TIMER2_COMPA_vect) {
feedback = adc_read(2); // fast ADC call
feedback = map (feedback, 0 , 1024 , 10 , 100); // map to min (10%) to max (100%)
PORTB ^= (1 << PB5);
TIFR2 = (1 << OCF2A);
}
uint16_t adc_read(uint8_t ch)
{
// select the corresponding channel 0~7
// ANDing with ’7′ will always keep the value
// of ‘ch’ between 0 and 7
ch &= 0b00000111; // AND operation with 7
ADMUX = (ADMUX & 0xF8) | ch; // clears the bottom 3 bits before ORing
// start single convertion
// write ’1′ to ADSC
ADCSRA |= (1 << ADSC);
// wait for conversion to complete
// ADSC becomes ’0′ again
// till then, run loop continuously
while (ADCSRA & (1 << ADSC));
return (ADC);
}
void loop() {
if (runXTimes < N) // softstart stuff
{
softstart ();
delayMicroseconds (71);
runXTimes++;
if ( runXTimes >= 20000)
{
PORTB = (0 << PB0);
settimers ();
}
}
}
