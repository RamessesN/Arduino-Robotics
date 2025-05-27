#ifndef MotionControl_H
#define MotionControl_H

#include "dataTrans.h"

#define THRESHOLD 1.0

float cal_error(IRStatus);
float calculate_pid(float);
void motor_control(float);
void lostLineHandling(float);

const int baseSpeed = 85;
const float max_pid = 50.0;

float Kp = 5.0;
float Ki = 0;
float Kd = 0;

int lostCount = 0;
const int lostThreshold = 10;

float last_valid_error = 0;

IRStatus old_status, new_status;

void carDrive() {
  old_status = new_status;
  new_status = statusDetect();

  float error = cal_error(new_status);

  if(error == 666) {
    lostCount++;
    if(lostCount >= lostThreshold) { // 超过10帧检测到离线触发
      lostLineHandling(last_valid_error);
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

void lostLineHandling(float last_error) {
  unsigned long startTime = millis();
  const unsigned long timeout = 800;

  if (last_error < 0) {
    turnLeft(false, true, 80, 155);
  } else {
    turnRight(true, false, 155, 80);
  }

  while (millis() - startTime < timeout) {
    IRStatus current = statusDetect();

    if (current.middle > THRESHOLD || current.left > THRESHOLD || current.right > THRESHOLD) {
      fullStop();
      return;
    }
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

float calculate_pid(float error) {
  static float I = 0;
  static float previous_error = 0;

  if (error != 666) {
    last_valid_error = error;
  }

  float P = error;
  I += error;
  I = constrain(I, -25, 25);
  float D = error - previous_error;

  float PID_value = (Kp * P) + (Ki * I) + (Kd * D);

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