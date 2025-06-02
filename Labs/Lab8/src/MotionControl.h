#ifndef MotionControl_H
#define MotionControl_H

#include "MotionSetting.h"

bool reverse = false;

const int baseSpeed = 150;

float lastTime = 0;

void carDrive(float altitude) {
  if(millis() - lastTime >= 100) {
    
  }
}

#endif