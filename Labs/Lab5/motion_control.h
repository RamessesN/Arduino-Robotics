#ifndef MotionControl_H
#define MotionControl_H

#define BORDER_VALUE 1.0

int baseSpeed = 150;
int sharp_turnSpeed = 110;
int subtle_turnSpeed = 100;

bool reverse = false;

void carDrive(float leftStatus, float middleStatus, float rightStatus) {
  fullStop();

  if(leftStatus < BORDER_VALUE && middleStatus < BORDER_VALUE && rightStatus < BORDER_VALUE) { // 000
    fullStop();
  } else if(leftStatus < BORDER_VALUE && middleStatus < BORDER_VALUE && rightStatus >= BORDER_VALUE) { // 001
    turnRight(reverse, sharp_turnSpeed);
  } else if(leftStatus < BORDER_VALUE && middleStatus >= BORDER_VALUE && rightStatus < BORDER_VALUE) { // 010
    goStraight(reverse, baseSpeed);
  } else if(leftStatus < BORDER_VALUE && middleStatus >= BORDER_VALUE && rightStatus >= BORDER_VALUE) { // 011
    turnRight(reverse, subtle_turnSpeed);
  } else if(leftStatus >= BORDER_VALUE && middleStatus < BORDER_VALUE && rightStatus < BORDER_VALUE) { // 100
    turnLeft(reverse, sharp_turnSpeed);
  } else if(leftStatus >= BORDER_VALUE && middleStatus < BORDER_VALUE && rightStatus >= BORDER_VALUE) { // 101
    goStraight(reverse, baseSpeed); // 不可能出现：判断是因为中间的缝隙导致，继续执行
  } else if(leftStatus >= BORDER_VALUE && middleStatus >= BORDER_VALUE && rightStatus < BORDER_VALUE) { // 110
    turnLeft(reverse, subtle_turnSpeed);
  } else if(leftStatus >= BORDER_VALUE && middleStatus >= BORDER_VALUE && rightStatus >= BORDER_VALUE) { // 111
    goStraight(reverse, baseSpeed);
  }
}

#endif