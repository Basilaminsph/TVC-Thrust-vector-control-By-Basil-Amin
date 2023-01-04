
#include <SD.h>
#include <SPI.h>


#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_I2CDevice.h>

Adafruit_BMP280 B28;
int ChipSelect = 0;


   String dataString = "";
void setup(){
!SD.begin(ChipSelect);
  
  B28.begin();
  B28.setSampling(Adafruit_BMP280::MODE_NORMAL,
    Adafruit_BMP280::SAMPLING_X2,
    Adafruit_BMP280::SAMPLING_X16,
    Adafruit_BMP280::FILTER_X16,
    Adafruit_BMP280::STANDBY_MS_500);
 
         File dataFile = SD.open("Flight.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
  
    Serial.println(dataString);
  }
}



void loop(){
      
 

  dataString += Serial.print("\t");
  dataString += Serial.print("\t");
  dataString += Serial.print(B28.readTemperature());
  Serial.print("\t");
  dataString += Serial.print(B28.readPressure());
  Serial.print("\t");
  dataString += Serial.print(B28.readAltitude(686.28976));
  Serial.print("\t");

}

  


