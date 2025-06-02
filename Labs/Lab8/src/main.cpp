#include "FactorDetect.h"
#include "MotionDetect.h"
#include "MotionSetting.h"
#include "MotionControl.h"

#include <Wire.h>

Adafruit_BME280 bme;
Adafruit_MPU6050 mpu;

void setup() {
  Wire.begin();
  Serial.begin(115200);
  while(!Serial);

  delay(1000);

  bme.begin(0x76);
  mpu.begin(0x68, &Wire);

  // Wheel Driver
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);
  // Light Driver
  pinMode(leftLightPin, OUTPUT);
  pinMode(rightLightPin, OUTPUT);
}

void loop() {
  bmePrint();
  mpuPrint();
  Serial.println();

  carDrive();

  delay(1000);
}