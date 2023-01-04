#include <Arduino.h>

#include <Adafruit_I2CDevice.h>

#include <SPI.h>

#include <Adafruit_Sensor.h>

#include <SD.h>

#include <SPIFlash.h>

#include <Wire.h>

#include <Adafruit_MPU6050.h>

#include <Servo.h>
Adafruit_MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;
Servo x1;
Servo y2;
void setup() {
  // put your setup code here, to run once:
  x1.attach(3);
  y2.attach(4);
  
   Serial.begin(9600);
   mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.println("");


}

void loop() {
 
  // put your main code here, to run repeatedly:
  x1.write(15);
  delay(10);
    x1.write(-15);
    delay(10);
      y2.write(15);
      delay(10);
        y2.write(-15);
        delay(10);
         x1.write(-15);
         delay(10);
    x1.write(15);
    delay(10);
      y2.write(-15);
      delay(10);
        y2.write(15);
        delay(10);
        sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /* Print out the values */
  Serial.print("AccelX:");
  Serial.print(a.acceleration.x);
  Serial.print(",");
  Serial.print("AccelY:");
  Serial.print(a.acceleration.y);
  Serial.print(",");
  Serial.print("AccelZ:");
  Serial.print(a.acceleration.z);
  Serial.print(", ");
  Serial.print("GyroX:");
  Serial.print(g.gyro.x);
  Serial.print(",");
  Serial.print("GyroY:");
  Serial.print(g.gyro.y);
  Serial.print(",");
  Serial.print("GyroZ:");
  Serial.print(g.gyro.z);
  Serial.println("");

      

}