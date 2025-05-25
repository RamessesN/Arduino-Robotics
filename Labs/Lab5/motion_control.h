#ifndef MotionControl_H
#define MotionControl_H

#define BORDER_VALUE 0.2

int baseSpeed = 90;
int sharp_turnSpeed = 200;
int subtle_turnSpeed = 100;

bool reverse = false;

void carDrive(float leftStatus, float middleStatus, float rightStatus) {
  fullStop();

  if(leftStatus < BORDER_VALUE && middleStatus < BORDER_VALUE && rightStatus >= BORDER_VALUE) { // 001
    turnRight(reverse, subtle_turnSpeed);
  } else if(leftStatus < BORDER_VALUE && middleStatus >= BORDER_VALUE && rightStatus < BORDER_VALUE) { // 010
    goStraight(reverse, baseSpeed);
  } else if(leftStatus < BORDER_VALUE && middleStatus >= BORDER_VALUE && rightStatus >= BORDER_VALUE) { // 011
    delay(50);
    crossRight(reverse, sharp_turnSpeed);
  } else if(leftStatus >= BORDER_VALUE && middleStatus < BORDER_VALUE && rightStatus < BORDER_VALUE) { // 100
    turnLeft(reverse, subtle_turnSpeed);
  } else if(leftStatus >= BORDER_VALUE && middleStatus >= BORDER_VALUE && rightStatus < BORDER_VALUE) { // 110
    delay(50);
    crossLeft(reverse, sharp_turnSpeed);
  } else {
    goStraight(reverse, baseSpeed);
  }
}

#endif