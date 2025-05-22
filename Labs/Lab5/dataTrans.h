#ifndef DataTransfer_H
#define DataTransfer_H

#include <ADS1115_WE.h>
#include <Wire.h>

extern ADS1115_WE adc;

struct IRStatus {
  float left;
  float middle;
  float right;
};

float readChannel(ADS1115_MUX channel) {
  adc.setCompareChannels(channel);
  return adc.getResult_V();
}

IRStatus statusDetect() {
  IRStatus status;
  status.left = readChannel(ADS1115_COMP_0_GND);
  status.middle = readChannel(ADS1115_COMP_1_GND);
  status.right = readChannel(ADS1115_COMP_2_GND);

  Serial.print("Left: ");
  Serial.print(status.left);
  Serial.print(" V; Middle: ");
  Serial.print(status.middle);
  Serial.print(" V; Right: ");
  Serial.print(status.right);
  Serial.println(" V");

  return status;
}

#endif