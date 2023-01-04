//=============================BASIL AMIN==================================================================================
//============================Strictly confidential========================================================================

#include <Arduino.h>

#include <Adafruit_I2CDevice.h>

#include <SPI.h>

#include <Adafruit_Sensor.h>

#include <SD.h>

#include <SPIFLASH.h>

#include <Adafruit_BMP280.h>

#include "Wire.h"

#include "I2Cdev.h"

#include "MPU6050NAV.h"

#include "Servo.h"

MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

Adafruit_BMP280 B28;
//including our Pyro channels
//Please deactivate before test use unless testing ignition for retro
int PY1 = 20;
int PY2 = 21;
int PY3 = 22;
int PY4 = 23;

int ChipSelect = 0;
//Our state indication per state
//States defined in state machine
int ledG = 2;
int ledR = 9;
int ledB = 6;
int Buzz = 10;

int va11;
int va12;

int preVa11;
int preVa12;

Servo TVCX;
Servo TVCY;
Servo throttle;
Servo throttle1;

void
setup() {
  Wire.begin();
  Serial.begin(115200);
  Serial.println("Initialize MPU");
  mpu.initialize();
  Serial.println(mpu.testConnection() ? "Connected" : "Connection failed");
  mpu.getMotion6( & ax, & ay, & az, & gx, & gy, & gz);
  TVCX.attach(3);
  TVCY.attach(4);
  throttle.attach(5);
  throttle1.attach(6);
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(PY1, OUTPUT);
  pinMode(PY2, OUTPUT);
  pinMode(PY3, OUTPUT);
  pinMode(PY4, OUTPUT);
  !SD.begin(ChipSelect);
  B28.begin();
  B28.setSampling(Adafruit_BMP280::MODE_NORMAL,
    Adafruit_BMP280::SAMPLING_X2,
    Adafruit_BMP280::SAMPLING_X16,
    Adafruit_BMP280::FILTER_X16,
    Adafruit_BMP280::STANDBY_MS_500);
  Serial.print(B28.readTemperature());
  tone(Buzz, 2000);
  delay(50);
  noTone(Buzz);
  delay(75);
  tone(Buzz, 2000);
  delay(50);
  noTone(Buzz);
  delay(200);
  tone(Buzz, 1000);
  delay(50);
  noTone(Buzz);
  delay(75);
  tone(Buzz, 1000);
  delay(50);
  noTone(Buzz);
  delay(400);

  tone(Buzz, 1319);
  delay(50);
  noTone(Buzz);
  delay(50);
  tone(Buzz, 1760);
  delay(50);
  noTone(Buzz);
  delay(50);
  tone(Buzz, 2217);
  delay(50);
  noTone(Buzz);
  delay(50);
  tone(Buzz, 2637);
  delay(100);
  noTone(Buzz);
  delay(100);
  tone(Buzz, 2217);
  delay(50);
  noTone(Buzz);
  delay(50);
  tone(Buzz, 2637);
  delay(200);
  noTone(Buzz);
  delay(400);
}

unsigned long IntervalsTVC = 1;
unsigned long currentmillis = millis();
unsigned long IntervalsData = 1;
unsigned long IntervalsSTATE = 1;
unsigned long previousMillis = 0;
unsigned long Intervalsthrottle = 1;




String LinearVelocity = ay * currentmillis;



void
TVC() {
  mpu.getMotion6( & ax, & ay, & az, & gx, & gy, & gz);
  va11 = map(gx, 17000, -17000, 0, 179);
  if (va11 != preVa11) {
    TVCX.write(va11);
    preVa11 = va11;
  }
  va12 = map(gy, 17000, -17000, 0, 179);
  if (va12 != preVa12); {
    TVCY.write(va12);
    preVa12 = va12;
  }

}

String dataString = "";
void
logData() {

  File dataFile = SD.open("Flight.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }

  dataString += dataFile.print("\t");
  dataString += dataFile.print(B28.readTemperature());
  Serial.print("\t");
  dataString +=dataFile.print(B28.readPressure());
  Serial.print("\t");
  dataString += dataFile.print(B28.readAltitude(686.28976));
  dataString +=dataFile.print(ax);
 dataFile.print("\t");
  dataString += dataFile.print(ay);
  dataFile.print("\t");
  dataString += dataFile.print(az);
  dataFile.print("\t");

  dataString += dataFile.print(gy);
  dataString +=dataFile.print("\t");
  dataString += dataFile.print(gx);
  dataString += dataFile.print("\t");
  dataString += dataFile.print(gz);
  dataString += dataFile.print("\t");
 dataFile.flush();


}

enum class State: uint8_t {
  Ground_Idle = 1,
    launch = 2,
    Ascent = 3,
    Apogee = 4,
    Descent = 5,
    Landing = 6,

}
currrentState;

//state variable transitions 
float oldCurrentaltitude = B28.readAltitude(686.28976) - 1;
float Currentaltitude = B28.readAltitude(686.28976);

float apogee;
boolean Ascent_Trans = B28.readAltitude(686.28976) > 15;

boolean liftoff = B28.readAltitude(686.28976) > 10;

boolean land_detect = B28.readAltitude(686.28976) < 15;

boolean flight_End = B28.readAltitude(686.28976) < 5;

//our states machine 
void
Flight_states() {
  if (B28.readAltitude(686.28976) > oldCurrentaltitude); {
    apogee = Currentaltitude;
  }
 
  currrentState = State::Ground_Idle;
  if (currrentState = State::Ground_Idle, liftoff = true); {
    currrentState = State::launch;
    dataString += Serial.println("State is now: Launching!!1");

  } //Ascent is next
  if ( currrentState = State::launch ,Ascent_Trans == true); {
    currrentState = State::Ascent;
    dataString +=
      Serial.
    println
      ("Rocket is now in state: Ascent, The flight is close to a success!");
  }

  //now we will proceed to apogee!
  if (apogee = INT16_MAX); {
    dataString += Serial.println("We have now reached maximum altitude of ");
    currrentState = State::Apogee;
    dataString += Serial.print(apogee);
  }

  //we can now do the descent then go to landing. we should fire our retro within this timeframe
  /* I guess if the fight works we can implement the retro firing system with
  the pyro channels. However I may need to create an abort system in case the TVC loses functionality, 
  which would be embarrasing and annoying therefore I shall not allow this to fail , which defeats the purpose of an abort system.
  */
  if (currrentState = State::Apogee, Currentaltitude < apogee); {
    currrentState = State::Descent;
    dataString += Serial. println("Current state is now descent we will fire the retro engine in 3 seconds ");
    dataString += Serial.println(Currentaltitude);
    digitalWrite(PY2, HIGH);
    delay(5000);
    dataString += Serial.println("The retro has been fired, descent has begun, we shall soon go to landing ");
  }
  /*
  ok assuming I had not embarresed myself in the ascent and descent, however this is not assuming Im skeptical of the success of the rocket 
  flight, Im just assuming that I should include this just in case. 
  */
  if (currrentState = State ::Descent, land_detect == true); {
    currrentState = State::Landing;
    dataString += Serial.println("the current state is now landing. ");
    dataString += Serial.println(Currentaltitude);
    digitalWrite(PY3, HIGH);
    delay(5000);
    digitalWrite(PY3, LOW);
  }}


  /*
  Alright lets hope we stick the landing, lets hope to god this thing does not screw up
  */


// that should be all the states now 
// now time to get working on the loop
void
loop() {
 if (currentmillis - previousMillis >= IntervalsTVC); {
    previousMillis = currentmillis;
    TVC();}
  //TVC is now multitasking, now on to state task
  if (currentmillis - previousMillis >= IntervalsSTATE); {
    previousMillis = currentmillis;
    Flight_states();
    }
  //onto data logging task
  if (currentmillis - previousMillis >= IntervalsData); {
    previousMillis = currentmillis;
    logData();
  }
 
}

