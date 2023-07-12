//=============================BASIL AMIN==================================================================================
//============================Strictly confidential========================================================================
//TVC landing code by Basil Amin
#include <Arduino.h>
#include <Adafruit_I2CDevice.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>


#include <SD.h>


#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Servo.h"

MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;


int PY1 = 20;
int PY2 = 21;
int va11;
int va12;

int preVa11;
int preVa12;

  Servo servo1;
  Servo servo2;

void setup()
{
  Wire.begin();
  Serial.begin(115200);
  Serial.println("Initialize MPU");
  mpu.initialize(); 
  Serial.println(mpu.testConnection() ? "Connected" : "Connection failed"); 
  servo1.attach(3);  
  servo2.attach(4);
    pinMode(PY1, OUTPUT);
  pinMode(PY2, OUTPUT);

}
void logdata(){
  int ChipSelect = 0;


   String dataString = "";
void setup();{
!SD.begin(ChipSelect);
  
  
         File dataFile = SD.open("Flight.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
  
    Serial.println(dataString);
  }
}
      
 
  dataString += Serial.print(gx);
  dataString += Serial.print("\t");
  dataString += Serial.print(gy);
  dataString += Serial.print("\t");
    dataString += Serial.print(gz);

  Serial.print("\t");
  dataString += Serial.print(ax);
  Serial.print("\t");
  dataString += Serial.print(az);
  Serial.print("\t");
  dataString += Serial.print(ay);
}

void loop()
{
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  va11 = map(ax, 17000, -17000, 0, 179);
  if (va11 != preVa11)
  {
    servo1.write(va11);
    preVa11 = va11;
  }
  va12 = map(ay, 17000, -17000, 0, 179);
  if (va12 != preVa12);
  { 
    servo2.write(va12);
    preVa12 = va12;
  }

 

  }

