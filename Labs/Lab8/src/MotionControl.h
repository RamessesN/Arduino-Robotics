#ifndef MotionControl_H
#define MotionControl_H

bool reverse = false;

int baseSpeed = 0;

void carDrive(float altitude) {
  if(altitude <= 0.05) {
    fullStop();
  }

  while(altitude += 0.1) {
    goStraight(reverse, baseSpeed += 10);
  }
}

#endif