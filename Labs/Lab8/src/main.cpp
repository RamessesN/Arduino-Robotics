#include "FactorDetect.h"
#include "MotionSetting.h"
#include "MotionControl.h"

Adafruit_BME280 bme;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  if(!bme.begin(0x76)) {
    Serial.println("ERROR: BME280 Read Failed!");
    while(1);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  float altitude = basicPrint();

  carDrive(altitude);
}

float basicPrint() {
  tempGet();
  presGet();
  float altitude = altGet();
  humGet();

  return altitude;
}