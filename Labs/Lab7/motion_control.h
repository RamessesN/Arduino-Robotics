#ifndef MotionControl_h
#define MotionControl_h

#define front_border_VALUE 30
#define side_border_VALUE 30
#define corner_safe_VALUE 25

int baseSpeed = 150;
int turnSpeed = 100;
int deceleratedSpeed = 110;

bool reverse = false;

enum ActionStep {
  STEP_IDLE,
  STEP_BACK,
  STEP_TURN_RIGHT_90,
  STEP_TURN_LEFT_90,
  STEP_DONE
};

ActionStep currentStep = STEP_IDLE;
unsigned long actionStartTime = 0;

void carDrive(float leftDist, float frontDist, float rightDist) {
  static bool inAction = false;

  if (inAction) {
    unsigned long now = millis();
    switch (currentStep) {
      case STEP_BACK:
        if (now - actionStartTime < 300) {
          goBack(reverse, deceleratedSpeed);
        } else {
          currentStep = STEP_TURN_RIGHT_90;
          actionStartTime = now;
        }
        return;

      case STEP_TURN_RIGHT_90:
        if (now - actionStartTime < 250) {
          turnRight(reverse, turnSpeed);
        } else {
          inAction = false;
          currentStep = STEP_IDLE;
        }
        return;

      case STEP_TURN_LEFT_90:
        if (now - actionStartTime < 250) {
          turnLeft(reverse, turnSpeed);
        } else {
          inAction = false;
          currentStep = STEP_IDLE;
        }
        return;

      default:
        fullStop();
        inAction = false;
        currentStep = STEP_IDLE;
        return;
    }
  }

  float leftSafeDist = (leftDist * frontDist) / sqrt(pow(leftDist, 2) + pow(frontDist, 2));
  float rightSafeDist = (rightDist * frontDist) / sqrt(pow(rightDist, 2) + pow(frontDist, 2));

  fullStop();

  if (leftSafeDist <= corner_safe_VALUE || rightSafeDist <= corner_safe_VALUE) {
    if (leftSafeDist <= corner_safe_VALUE && rightSafeDist <= corner_safe_VALUE) { // 00 - 卡墙角
      currentStep = STEP_BACK;
      inAction = true;
      actionStartTime = millis();
      return;
    } else if (leftSafeDist <= corner_safe_VALUE && rightSafeDist > corner_safe_VALUE) { // 01
      inAction = true;
      actionStartTime = millis();
      return;
    } else if (leftSafeDist > corner_safe_VALUE && rightSafeDist <= corner_safe_VALUE) { // 10
      inAction = true;
      actionStartTime = millis();
      return;
    } else if (leftSafeDist > corner_safe_VALUE && rightSafeDist > corner_safe_VALUE) { // 11
      goStraight(reverse, deceleratedSpeed, deceleratedSpeed);
      return;
    } else {
      fullStop();
      return;
    }
  } else {
    if (leftDist <= side_border_VALUE && frontDist <= front_border_VALUE && rightDist <= side_border_VALUE) { // 000
      currentStep = STEP_BACK;
      inAction = true;
      actionStartTime = millis();
      currentStep = STEP_TURN_RIGHT_90;
      return;
    } else if (leftDist <= side_border_VALUE && frontDist <= front_border_VALUE && rightDist > side_border_VALUE) { // 001
      inAction = true;
      actionStartTime = millis();
      currentStep = STEP_TURN_RIGHT_90;
      return;
    } else if (leftDist > side_border_VALUE && frontDist <= front_border_VALUE && rightDist <= side_border_VALUE) { // 100
      inAction = true;
      actionStartTime = millis();
      currentStep = STEP_TURN_LEFT_90;
      return;
    } else { // 010, 011, 101, 110, 111
      goStraight(reverse, baseSpeed, baseSpeed);
    }
  }
}

#endif