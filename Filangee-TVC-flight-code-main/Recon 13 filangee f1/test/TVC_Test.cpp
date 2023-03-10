#include <Arduino.h>
#include <Adafruit_I2CDevice.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>



//Gimbal code for TVC Rocket project - James Francis

//Make sure to download all the libraries listed below, or else code won't Compile

//Original Code by Niket Shah Plus on Youtube



#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Servo.h"

MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;



int va11;
int va12;

int preVa11;
int preVa12;

  Servo servo1;
  Servo servo2;

void setup()
{
  Wire.begin();
  Serial.begin(115200); // When in the serial monitor make sure Baud rate is at 115200
  Serial.println("Initialize MPU");
  mpu.initialize(); 
  Serial.println(mpu.testConnection() ? "Connected" : "Connection failed"); 
  servo1.attach(3);  //Attach servos to pin D5 and D6
  servo2.attach(4);
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
