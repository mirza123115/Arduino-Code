 #include<SoftwareSerial.h>  //suart
SoftwareSerial SUART(2, 3);  //SRXD = DPin-2, STXD = DPin-3 ;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);//UART
   SUART.begin(9600); //SUART
  // put your main code here, to run repeatedly:
while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}
char  y;

 byte myData[20]={"0x00"};
void loop() {
 int n=SUART.available() ;


  if (n>0) {
    // read the incoming byte:
 /* y = SUART.read();
  //SUART.write(y);
 // Serial.print("I received: ");
    Serial.println(y);*/
    //delay(5);

    


   byte m = SUART.readBytesUntil('\n', myData, 20); //detcet NewLine charcater but does not save
   myData[m] = '\0';  //insert null-byte as the last element in the array myData[]
   int recData = atoi(myData);   //myData[] array must be null-byte termination*/
  // byte recData = (myData[0] << 4)|(myData[1] & 0x0F); //31=>10|02 => 12 = 00010011 binary
//recData = (recData>>4)*0x0A + (recData & 0x0F)*0x01 ;//==> 0x0A + 0x02 = 0x0C ==> 12 decimal
float k= recData /1000;
Serial.println(recData); //shows: 12 decimal
  
}
}

/*void serialEvent()
{
    y = Serial.read();
  SUART.write(y);

}*/
