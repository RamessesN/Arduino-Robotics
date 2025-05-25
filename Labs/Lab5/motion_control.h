#ifndef MotionControl_H
#define MotionControl_H

#define BORDER_VALUE 0.2

int baseSpeed = 90;
int sharp_turnSpeed = 200;
int subtle_turnSpeed = 100;

bool reverse = false;

void carDrive(float leftStatus, float middleStatus, float rightStatus) {
  // fullStop();

  if(leftStatus < BORDER_VALUE && middleStatus < BORDER_VALUE && rightStatus >= BORDER_VALUE) { // 001
    turnRight(reverse, sharp_turnSpeed);
  } else if(leftStatus < BORDER_VALUE && middleStatus >= BORDER_VALUE && rightStatus >= BORDER_VALUE) { // 011
    turnRight(reverse, subtle_turnSpeed);
  } else if(leftStatus >= BORDER_VALUE && middleStatus >= BORDER_VALUE && rightStatus < BORDER_VALUE) { // 110
    turnLeft(reverse, subtle_turnSpeed);
  } else if(leftStatus >= BORDER_VALUE && middleStatus < BORDER_VALUE && rightStatus < BORDER_VALUE) { // 100
    turnLeft(reverse, sharp_turnSpeed);
  } else { // mainly 010
    goStraight(reverse, baseSpeed);
  }
}

#endif