#ifndef MotionControl_H
#define MotionControl_H

#define BORDER_VALUE 0.2

enum Direction {
  DIR_STRAIGHT,
  DIR_LEFT,
  DIR_RIGHT
};

Direction lastDirection  = DIR_STRAIGHT;

bool reverse = false;

void mainTrackMethod(float middleStatus) {
  if(middleStatus >= BORDER_VALUE) {
    goStraight(reverse, 120);
    lastDirection = DIR_STRAIGHT;
  } else {
    if(lastDirection == DIR_LEFT) {
      turnLeft(reverse, 100);
    } else if(lastDirection == DIR_RIGHT) {
      turnRight(reverse, 100);
    } else {
      goStraight(reverse, 120);
    }
  }
}

void carDrive(float leftStatus, float middleStatus, float rightStatus) {
  fullStop();

  if(leftStatus < BORDER_VALUE && middleStatus < BORDER_VALUE && rightStatus >= BORDER_VALUE) {
    turnRight(reverse, 100); // 001
    lastDirection = DIR_RIGHT;
  } else if(leftStatus >= BORDER_VALUE && middleStatus < BORDER_VALUE && rightStatus < BORDER_VALUE) {
    turnLeft(reverse, 100);  // 100
    lastDirection = DIR_LEFT;
  } else {
    mainTrackMethod(middleStatus);
  }
}

#endif