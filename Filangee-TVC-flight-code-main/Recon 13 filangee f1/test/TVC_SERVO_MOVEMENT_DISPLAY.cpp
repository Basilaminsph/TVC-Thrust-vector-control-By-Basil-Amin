#include <Arduino.h>
#include <Adafruit_I2CDevice.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>





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
  Serial.begin(115200);
  Serial.println("Initialize MPU");
  mpu.initialize(); 
  Serial.println(mpu.testConnection() ? "Connected" : "Connection failed"); 
  servo1.attach(3);  
  servo2.attach(4);
}


void print_gyData(){Serial.print("ax =");
Serial.print(ax);
Serial.println("az =");
Serial.print(az);
Serial.println("ay =");
Serial.print(ay);
Serial.println("gy =");
Serial.print(gy);
Serial.println("gx =");
Serial.print(gx);
Serial.println("gz =");
Serial.print(gz);}

void loop(){
servo1.write(20);
servo1.write(-20);

servo2.write(20);
servo2.write(20);

servo1.write(-20);
servo1.write(20);

servo2.write(-20);
servo2.write(20);

print_gyData();
}
