#ifndef EngineControl_H
#define EngineControl_H

#include <Servo.h>
Servo MyServo;

int prev_angle = 0;

int servoRotate() {
  MyServo.write(prev_angle);
  delay(200);
  int curr_angle = prev_angle;
  if(prev_angle > 180) {
    prev_angle = 0;
  }
  return curr_angle;
}

#endif