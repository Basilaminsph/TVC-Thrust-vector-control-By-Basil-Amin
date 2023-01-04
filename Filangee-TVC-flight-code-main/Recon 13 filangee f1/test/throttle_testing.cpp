#include<Arduino.h>

#include "Wire.h"

#include "I2Cdev.h"

#include "MPU6050.h"

#include "Servo.h"

Servo Throttle1; 
Servo Throttle2;

void setup(){
Throttle1.attach(5);
Throttle2.attach(6);
Serial.begin(9600);
}
void loop() {
    Throttle1.write(5);
    Throttle2.write(-5);
      Throttle1.write(10);
    Throttle2.write(-10);
}