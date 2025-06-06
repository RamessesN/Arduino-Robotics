#ifndef MotionControl_h
#define MotionControl_h

#define front_border_VALUE 40
#define side_border_VALUE 40
#define corner_safe_VALUE 25

int baseSpeed = 200;
int turnSpeed = 100;
int deceleratedSpeed = 110;

bool reverse = false;

enum ActionStep {
  STEP_IDLE,
  STEP_BACK,
  STEP_BACK_EXTRA,
  STEP_TURN_RIGHT_90,
  STEP_DONE
};

ActionStep currentStep = STEP_IDLE;
unsigned long actionStartTime = 0;
unsigned long lastActionEndTime = 0;
bool inAction = false;
bool recentlyAvoidedCorner = false;

void carDrive(float leftDist, float frontDist, float rightDist) {
  if (!inAction) {
    if(recentlyAvoidedCorner && millis() - lastActionEndTime < 800) {
      fullStop();
      return;
    } else {
      recentlyAvoidedCorner = false;
    }
  }

  if (inAction) {
    unsigned long now = millis();
    switch (currentStep) {
      case STEP_BACK:
        if (now - actionStartTime < 100) {
          goBack(reverse, deceleratedSpeed);
        } else {
          if (rightDist <= side_border_VALUE) {
            currentStep = STEP_BACK_EXTRA;
          } else {
            currentStep = STEP_TURN_RIGHT_90;
          }
          actionStartTime = now;
        }
        return;

      case STEP_BACK_EXTRA:
        if (now - actionStartTime < 100) {
          goBack(reverse, deceleratedSpeed);
        } else {
          currentStep = STEP_TURN_RIGHT_90;
          actionStartTime = now;
        }
        return;

      case STEP_TURN_RIGHT_90:
        if (now - actionStartTime < 300) {
          turnRight(reverse, turnSpeed);
        } else {
          currentStep = STEP_DONE;
          actionStartTime = now;
        }
        return;

      case STEP_DONE:
        fullStop();
        inAction = false;
        currentStep = STEP_IDLE;
        lastActionEndTime = millis();
        recentlyAvoidedCorner = true;
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
    currentStep = STEP_BACK;
    inAction = true;
    actionStartTime = millis();
    return;
  }

  if (frontDist <= front_border_VALUE) {
    currentStep = STEP_BACK;
    inAction = true;
    actionStartTime = millis();
    return;
  }

  goStraight(reverse, baseSpeed);
}

#endif