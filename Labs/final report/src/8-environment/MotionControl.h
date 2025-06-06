#ifndef MotionControl_H
#define MotionControl_H

#include "MotionSetting.h"

bool reverse = false;
int baseSpeed = 150;

bool isLifted = false;

const float LIFT_THRESHOLD = 8.5f;
const float GROUND_THRESHOLD = 10.0f;
const unsigned long DEBOUNCE_TIME = 250;

void carDrive() {
  getVariables();
  static unsigned long lastStateChangeTime = 0;
  static bool stableState = false;

  float acc = sqrt(pow(accData.x, 2) + pow(accData.y, 2) + pow(accData.z, 2));

  bool stateChanged = false;
  unsigned long currentTime = millis();

  if (stableState) {
    if (acc >= GROUND_THRESHOLD) {
      if (lastStateChangeTime == 0) {
        lastStateChangeTime = currentTime;
      } else if (currentTime - lastStateChangeTime >= DEBOUNCE_TIME) {
        stableState = false;
        isLifted = false;
        stateChanged = true;
        lastStateChangeTime = 0;
      }
    } else {
      lastStateChangeTime = 0;
    }
  } else {
    if (acc <= LIFT_THRESHOLD) {
      if (lastStateChangeTime == 0) {
        lastStateChangeTime = currentTime;
      }
      else if (currentTime - lastStateChangeTime >= DEBOUNCE_TIME) {
        stableState = true;
        isLifted = true;
        stateChanged = true;
        lastStateChangeTime = 0;
      }
    } else {
      lastStateChangeTime = 0;
    }
  }

  if(isLifted) {
    goStraight(reverse, baseSpeed);
  } else {
    fullStop();
  }
}

#endif