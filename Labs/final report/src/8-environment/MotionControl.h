#ifndef MotionControl_H
#define MotionControl_H

#include "MotionSetting.h"

bool reverse = false;
int baseSpeed = 150;

bool isLifted = false;

unsigned long lastCheckTime = 0;

void carDrive() {
  unsigned long now = millis();
  if(now - lastCheckTime >= 100) {
    lastCheckTime = now;

    variables acc, gyro;
    getVariables(acc, gyro);

    float acc_z = acc.z;

    if(!isLifted && acc_z < 7.0) { // Up
      isLifted = true;
      Serial.println("UP!!!");
      goStraight(reverse, baseSpeed);
    } else if(isLifted && acc_z > 7.0) { // Down
      isLifted = false;
      Serial.println("Down!!!");
      fullStop();
    }
  }
}

#endif