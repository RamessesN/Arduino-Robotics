#ifndef EngineControl_h
#define EngineControl_h

#include <Servo.h>
Servo MyServo;

int angles[] = {0, 90, 180, 90};
int curr = 0;

int servoRotate() {
  int angle = angles[curr];
  MyServo.write(angle);
  delay(500);

  curr = (curr + 1) % 4;
  return angle;
}

#endif