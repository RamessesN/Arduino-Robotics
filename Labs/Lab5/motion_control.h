#ifndef MotionControl_H
#define MotionControl_H

#include "dataTrans.h"

#define THRESHOLD 1.0

float cal_error(IRStatus);
bool big_error(float, float);
float calculate_pid(float);
void motor_control(float);
void lostLineHandling(IRStatus);

const int baseSpeed = 85;
const float max_pid = 50.0;

float Kp = 5.0;
float Ki = 0;
float Kd = 0;

int lostCount = 0;
const int lostThreshold = 10;

IRStatus old_status, new_status;

void carDrive() {
  old_status = new_status;
  new_status = statusDetect();

  float error = cal_error(new_status);

  if(error == 666) {
    lostCount++;
    if(lostCount >= lostThreshold) { // 超过10帧检测到离线触发
      lostLineHandling(old_status);
      lostCount = 0;
    }
  } else {
    lostCount = 0;
    float pid_val = calculate_pid(error);
    motor_control(pid_val);
  }

  Serial.print("Error: ");
  Serial.println(error);
}

void lostLineHandling(IRStatus old_status) {
  unsigned long startTime = millis();
  const unsigned long timeout = 500;

  while (millis() - startTime < timeout) {
    IRStatus current = statusDetect();

    if (current.middle > THRESHOLD || current.left > THRESHOLD || current.right > THRESHOLD) {
      fullStop();
      return;
    }

    if (old_status.left <= THRESHOLD && old_status.right > THRESHOLD) {
      turnRight(true, false, (255 - 65), 65);
    } else if (old_status.right <= THRESHOLD && old_status.left > THRESHOLD) {
      turnLeft(false, true, 65, (255 - 65));
    } else {
      turnRight(false, true, 65, (255 - 65));
    }

    delay(50);
  }

  fullStop();
}

float cal_error(IRStatus status) {
  float error = status.left - status.right;
  if (status.middle <= THRESHOLD) {
    if (status.left > THRESHOLD) {
      error = 9 - status.left;
    } else if (status.right > THRESHOLD) {
      error = status.right - 9;
    } else {
      error = 666;
    }
  }
  return error;
}

bool big_error(float error, float max_error) {
  if (error > max_error) {
    motor_control(max_pid);
    return true;
  }
  if (error < -max_error) {
    motor_control(-max_pid);
    return true;
  }
  return false;
}

float calculate_pid(float error) {
  float P = 0, I = 0, D = 0, PID_value = 0, previous_error = 0;

  P = error;
  I += error;
  I = constrain(I, -25, 25);
  D = error - previous_error;

  PID_value = (Kp * P) + (Ki * I) + (Kd * D);

  previous_error = error;

  return constrain(PID_value, -max_pid, max_pid);
}

void motor_control(float PID_value) {
  int left_motor_speed = baseSpeed - PID_value;
  int right_motor_speed = baseSpeed + PID_value;

  left_motor_speed = constrain(left_motor_speed, 50, 200);
  right_motor_speed = constrain(right_motor_speed, 50, 200);

  goStraight(false, left_motor_speed, right_motor_speed);
}

#endif