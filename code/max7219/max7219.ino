#include<SPI.h>
byte registerAddress[] = {0x09, 0x0A, 0x0B, 0x0C};//Registers of MAX7219 to be initialized
byte registerData[] = {0x00, 0x01, 0x03, 0x01};    //data for registers of AMX7219
byte dataArray[4] = {0x6D, 0x70, 0x5F, 0x5B}; //cc-code for 2 7. 65 (no-decode format)
byte digitAddress[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};//digit address

void setup()
{
    pinMode(10, OUTPUT);  //LOAD Pin of MAX7219
    //-------------------
    SPI.begin();
    bitSet(SPCR, 4);              //UNO is Master SPI
    SPI.setBitOrder(MSBFIRST);    //MSB_bit will be transferred first
    SPI.setClockDivider(SPI_CLOCK_DIV128); //TX rate = 16MHz/128 = 125 kbit
    SPI.setDataMode(SPI_MODE1);//MOSI is sampled at the rising edge of CLK
    //------------------------------------------------
    digitalWrite(10, LOW);      //Low at LOAD pin
    //---- computation----------------------------------
    //byte z = 0x12 + 0x13;   //z = 3C
   // dataArray[0] = lupTable[z>>4];
    //dataArray[1] = lupTable[z&0x0F];
    //-------------------------------------------------
    
    //---keep intializing the Mode of Operation------------
    for(int i=0; i<4; i++)
    {
      SPI.transfer(registerAddress[i]);
      SPI.transfer(registerData[i]);
      digitalWrite(10, LOW);
      digitalWrite(10, HIGH); //assert LH/LL on LOAD pin
      digitalWrite(10, LOW);
    }
  
    //--keep transferring the result/data----------------------
    for(int i=0; i<4; i++)
    {
      SPI.transfer(digitAddress[i]); //DPX position
      SPI.transfer(dataArray[i]);   //shows 2 on DP0-position
      digitalWrite(10, LOW);
      digitalWrite(10, HIGH);       //assert LH/LL on LOAD pin
      digitalWrite(10, LOW);
    }
 }

 void loop()
 {
  
 }
