#include "MQ135/MQ135.h"

#define RED 5
#define ORANGE 4
#define GREEN 3

#define RANG1 700
#define RANG2 1500

MQ135 gasSensor = MQ135(A2);

void setup() {
  Serial.begin(9600);
  pinMode(RED, OUTPUT);
  pinMode(ORANGE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  digitalWrite(RED, LOW);
}

void critical() {
  digitalWrite(GREEN, LOW);
  digitalWrite(ORANGE, LOW);
  digitalWrite(RED, HIGH);
}

void warning() {
  digitalWrite(GREEN, LOW);
  digitalWrite(ORANGE, HIGH);
  digitalWrite(RED, LOW);
  
}

void ok() {
  digitalWrite(GREEN, HIGH);
  digitalWrite(ORANGE, LOW);
  digitalWrite(RED, LOW);
  
}


void calibration() {
  float rzero = gasSensor.getRZero();
  Serial.print("rzero: ");
  Serial.println(rzero);
  delay(100);
}

void loop() {

  //calibration();
  
  float ppm = gasSensor.getPPM();
  Serial.print("ppm:");
  Serial.println(ppm);
  if (ppm < RANG1) {
    ok();
  } else if(ppm >= RANG1 && ppm <RANG2) {
    warning();
  } else if (ppm>=RANG2) {
    critical();
  }

  
  delay(100);
}

