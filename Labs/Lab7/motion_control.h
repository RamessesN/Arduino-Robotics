#ifndef MotionControl_h
#define MotionControl_h

void carDrive(float leftDist, float frontDist, float rightDist) {
  if(leftDist < 50 && frontDist < 50 && rightDist < 50) { // 000
    fullStop(reverse);
    goBack(reverse, baseSpeed);
  } else if(leftDist < 50 && frontDist < 50 && rightDist > 50) { // 001
    fullStop(reverse);
    turnRight(reverse, baseSpeed);
  } else if(leftDist < 50 && frontDist > 50  && rightDist < 50) { // 010
    fullStop(reverse);
    goStraight(reverse, baseSpeed);
  } else if(leftDist < 50 && frontDist > 50  && rightDist > 50) { // 011
    fullStop(reverse);
    goStraight(reverse, baseSpeed); // 向前优先
  } else if(leftDist > 50 && frontDist < 50  && rightDist < 50) { // 100
    fullStop(reverse);
    turnLeft(reverse, baseSpeed);
  } else if(leftDist > 50 && frontDist < 50  && rightDist > 50) { // 101
    fullStop(reverse);
    turnRight(reverse, baseSpeed); // 右转优先
  } else if(leftDist > 50 && frontDist > 50  && rightDist < 50) { // 110
    fullStop(reverse);
    goStraight(reverse, baseSpeed); // 向前优先
  } else if(leftDist > 50 && frontDist > 50  && rightDist > 50) { // 111
    fullStop(reverse);
    goStraight(reverse, baseSpeed); // 向前优先
  } else {
    fullStop(reverse);
  }
}

#endif