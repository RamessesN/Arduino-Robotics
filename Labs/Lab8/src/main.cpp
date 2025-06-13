#include "FactorDetect.h"
#include "LCDDemonstrate.h"
#include "MotionDetect.h"
#include "MotionSetting.h"
#include "MotionControl.h"

#include <Wire.h>

Adafruit_BME280 bme;
Adafruit_MPU6050 mpu;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Wire.begin();
  Serial.begin(115200);
  while(!Serial);

  delay(1000);

  bme.begin(0x76);
  mpu.begin(0x68, &Wire);
  lcd.init();
  lcd.backlight();

  // Wheel Driver
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);
  // Light Driver
  pinMode(leftLightPin, OUTPUT);
  pinMode(rightLightPin, OUTPUT);
}

variables accData;
variables gyroData;

unsigned long lastPrintTime = 0;

void loop() {
  carDrive();

  static bool basicShown = false;
  if (!basicShown) {
    basicDemonstrate();
    basicShown = true;
    delay(2500);
    lcd.clear();
  }

  bmeDemonstrate();
  mpuDemonstrate();

  static unsigned long lastPrintTime = 0;
  unsigned long currentTime = millis();
  if(currentTime - lastPrintTime >= 1000) {
    bmePrint();
    mpuPrint();
    Serial.println();

    lastPrintTime = currentTime;
  }
}