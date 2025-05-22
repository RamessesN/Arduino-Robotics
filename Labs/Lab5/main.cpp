#include "motion_setting.h"
#include "motion_control.h"
#include "dataTrans.h"

#define I2C_ADDRESS 0x48

ADS1115_WE adc = ADS1115_WE(I2C_ADDRESS);

void setup() {
  Wire.begin();
  Serial.begin(9600);

  if(!adc.init()) {
    Serial.println("ERROR: ADS1115 connected failed!");
  }

  adc.setVoltageRange_mV(ADS1115_RANGE_6144);
  adc.setMeasureMode(ADS1115_CONTINUOUS);

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
  IRStatus status = statusDetect();
  carDrive(status.left, status.middle, status.right);
}
