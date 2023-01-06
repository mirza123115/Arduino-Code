#include <Wire.h>
#include "BlueDot_BME280.h"

BlueDot_BME280 bme;
int bmeDetected = 0;    //Checks if Sensor 1 is available

void setup()
{
  Serial.begin(9600);
  Serial.println(F("Basic Weather Station"));
  
  bme.parameter.communication = 0;                    //I2C communication for Sensor  (bme1)
  bme.parameter.I2CAddress = 0x76;                    //I2C Address for Sensor  (bme1)
  bme.parameter.sensorMode = 0b11;                    //Setup Sensor mode for Sensor
  bme.parameter.IIRfilter = 0b100;                   //IIR Filter for Sensor
  bme.parameter.humidOversampling = 0b101;            //Humidity Oversampling for Sensor
  bme.parameter.tempOversampling = 0b101;              //Temperature Oversampling for Sensor
  bme.parameter.pressOversampling = 0b101;             //Pressure Oversampling for Sensor
  bme.parameter.pressureSeaLevel = 1013.25;            //default value of 1013.25 hPa (Sensor)
  bme.parameter.tempOutsideCelsius = 15;               //default value of 15°C

  if (bme.init() != 0x60)
  {
    Serial.println(F("Ops! First BME280 Sensor not found!"));
    bmeDetected = 0;
    while (1); //wait for ever
  }
  else
  {
    Serial.println(F("First BME280 Sensor detected!"));
    bmeDetected = 1;
  }

  Serial.println();
  Serial.println();
}

void loop()
{
  Serial.print("Temperature Sensor [°C]:  ");
  float bmeTemp = bme.readTempC();
  Serial.println(bmeTemp, 2);
  //------------------------------------------
  Serial.print("Humidity Sensor [%]:     ");
  float bmeHumid = bme.readHumidity();
  Serial.println(bmeHumid, 2);
  //-------------------------------------------
  Serial.print("Pressure Sensor [hPa]:  ");
  float bmePress = bme.readPressure();
  Serial.println(bmePress, 2);
  //--------------------------------------------
  Serial.print("Altitude Sensor [m]:      ");
  float bmeAlt = bme.readAltitudeMeter();
  Serial.println(bmeAlt, 2);
  //----------------------------------------------
  Serial.println("****************************************");
  Serial.println();
  
  delay(3000);  //test interval
}
