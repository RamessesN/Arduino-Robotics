#ifndef MotionControl_h
#define MotionControl_h

#define front_border_VALUE 30
#define side_border_VALUE 45

enum CarState {
  IDLE,
  BACKING,
  TURNING_RIGHT,
  TURNING_LEFT,
  BUFFERING,
  JUST_TURNED
};

CarState carState = IDLE;

int baseSpeed = 130;
int turnSpeed = 100;
int deceleratedSpeed = 110;

bool reverse = false;

unsigned long stepStartTime = 0;
unsigned long backDuration = 500;
unsigned long turnDuration = 400;
unsigned long bufferDuration = 50;
unsigned long shortBackDuration = 200;
unsigned long shortTurnDuration = 200;

float lastLeft = 0, lastFront = 0, lastRight = 0;

void carDrive(float leftDist, float frontDist, float rightDist) {
  unsigned long currentMillis = millis();

  switch (carState) {
    case IDLE:
      fullStop();

      if (leftDist < side_border_VALUE && frontDist < front_border_VALUE && rightDist < side_border_VALUE) { // 000
        if (leftDist < 30 || rightDist < 30) {
          goBack(reverse, baseSpeed);
          stepStartTime = currentMillis;
          carState = BACKING;
        } else {
          goBack(reverse, baseSpeed);
          stepStartTime = currentMillis;
          backDuration = 500;
          carState = BACKING;
        }
      }
      else if (leftDist < side_border_VALUE && frontDist < front_border_VALUE && rightDist > side_border_VALUE) { // 001
        if (leftDist < 30 || rightDist < 30) {
          goBack(reverse, baseSpeed);
          stepStartTime = currentMillis;
          carState = BACKING;
        } else {
          goBack(reverse, baseSpeed);
          stepStartTime = currentMillis;
          backDuration = 500;
          carState = BACKING;
        }
      }
      else if (leftDist > side_border_VALUE && frontDist < front_border_VALUE && rightDist < side_border_VALUE) { // 100
        if (leftDist < 30 || rightDist < 30) {
          goBack(reverse, baseSpeed);
          stepStartTime = currentMillis;
          carState = BACKING;
        } else {
          goBack(reverse, baseSpeed);
          stepStartTime = currentMillis;
          backDuration = 500;
          carState = BACKING;
        }
      }
      else if (leftDist > side_border_VALUE && frontDist < front_border_VALUE && rightDist > side_border_VALUE) { // 101
        if (leftDist < 30 || rightDist < 30) {
          goBack(reverse, baseSpeed);
          stepStartTime = currentMillis;
          carState = BACKING;
        } else {
          goBack(reverse, baseSpeed);
          stepStartTime = currentMillis;
          backDuration = 500;
          carState = BACKING;
        }
      }
      else { // 直线速度补偿机制
        if (leftDist >= side_border_VALUE && leftDist <= 80 && rightDist > 80) {
          goStraight(reverse, deceleratedSpeed, 1.1 * deceleratedSpeed);
        }
        else if (leftDist < side_border_VALUE) {
          fullStop();
          stepStartTime = currentMillis;
          carState = BUFFERING;
        }
        else if (rightDist >= side_border_VALUE && rightDist <= 80 && leftDist > 80) {
          goStraight(reverse, 1.1 * deceleratedSpeed, deceleratedSpeed);
        }
        else if (rightDist < side_border_VALUE) {
          fullStop();
          stepStartTime = currentMillis;
          carState = BUFFERING;
        }
        else {
          goStraight(reverse, baseSpeed, baseSpeed);
        }
      }

      lastLeft = leftDist;
      lastFront = frontDist;
      lastRight = rightDist;
      break;

    case BACKING:
      if (currentMillis - stepStartTime >= backDuration) {
        fullStop();
        stepStartTime = currentMillis;

        if (lastLeft < 50) {
          turnRight(reverse, turnSpeed);
          carState = TURNING_RIGHT;
        } else if (lastRight < 50) {
          turnLeft(reverse, turnSpeed);
          carState = TURNING_LEFT;
        } else { // 右转优先
          if (lastRight > side_border_VALUE) {
            turnRight(reverse, turnSpeed);
            carState = TURNING_RIGHT;
          } else {
            turnLeft(reverse, turnSpeed);
            carState = TURNING_LEFT;
          }
        }
        stepStartTime = currentMillis;
        turnDuration = 400;
      }
      break;

    case TURNING_RIGHT:
    case TURNING_LEFT:
      if (currentMillis - stepStartTime >= turnDuration) {
        fullStop();
        carState = JUST_TURNED;
      }
      break;

    case BUFFERING:
      if (currentMillis - stepStartTime >= bufferDuration) {
        goBack(reverse, deceleratedSpeed);
        stepStartTime = currentMillis;
        backDuration = shortBackDuration;
        carState = BACKING;
      }
      break;

    case JUST_TURNED:
      carState = IDLE;
      break;
  }
}

#endif