//including our Pyro channels
//Please deactivate before test use unless testing ignition for retro
#include <Arduino.h>
int PY1 = 20;
int PY2 = 21;
int PY3 = 22;
int PY4 = 23;

void setup(){
  pinMode(PY1, OUTPUT);
  pinMode(PY2, OUTPUT);
  pinMode(PY3, OUTPUT);
  pinMode(PY4, OUTPUT);
Serial.begin(9600);
}

void main(){
    Serial.println("Pyro one firing in 10 seconds");
    delay(10000);
    digitalWrite(PY1, HIGH);
    delay(5000);
    digitalWrite(PY1, LOW);
    Serial.println("We finished with pyro 1, now onto pyro 2");
    delay(10000);
    digitalWrite(PY2, HIGH);
    delay(5000);
    digitalWrite(PY2, LOW);
    Serial.println("Now we can move onto pyro 3");
        delay(10000);
    digitalWrite(PY3, HIGH);
    delay(5000);
    digitalWrite(PY3, LOW);
    Serial.println("we can now go onto pyro 4");
        delay(10000);
    digitalWrite(PY4, HIGH);
    delay(5000);
    digitalWrite(PY4, LOW);
    Serial.println("Thats all pyros completed, we havee now finished our pyrotechnics assesment.");
}